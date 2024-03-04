// Fill out your copyright notice in the Description page of Project Settings.

#include "EnhancedInputSubsystems.h"
#include "Input/AuraEnhancedInputComponent.h"
#include "Interfaces/TargetInterface.h"
#include "Player/AuraHUD.h"
#include "Ability/MasterAbilityComponent.h"
#include "Components/SplineComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Pawn.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Player/AuraController.h"

AAuraController::AAuraController()
{
	bReplicates = true;
	PathSpline = CreateDefaultSubobject<USplineComponent>(TEXT("FollowPath"));
	
}


void AAuraController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeParams;
	InputModeParams.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeParams.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeParams);

}


void AAuraController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	TraceMouseCursor();
	AutoRun();
}

void AAuraController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* CurrentPawn = GetPawn())
	{
		const FVector ClosestSplinePoint = PathSpline->FindLocationClosestToWorldLocation(CurrentPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = PathSpline->FindDirectionClosestToWorldLocation(ClosestSplinePoint, ESplineCoordinateSpace::World);
		CurrentPawn->AddMovementInput(Direction);
		const float DistanceToDestinationPoint = (ClosestSplinePoint - CachedDestination).Length();
		if (DistanceToDestinationPoint <= AutoRunAcceptanceRadius) bAutoRunning = false;
	}
}

//Setup InputComponent and Actions
void AAuraController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraEnhancedInputComponent* AuraEnhancedInput = CastChecked<UAuraEnhancedInputComponent>(InputComponent);
	AuraEnhancedInput->BindAction(IAMove, ETriggerEvent::Triggered, this, &AAuraController::MoveAura);
	AuraEnhancedInput->BindAction(IAShift, ETriggerEvent::Started, this, &AAuraController::ShiftPressed);
	AuraEnhancedInput->BindAction(IAShift, ETriggerEvent::Completed, this, &AAuraController::ShiftReleased);

	AuraEnhancedInput->BindAction(IAAttributeOverlay, ETriggerEvent::Started, this, &AAuraController::OpenCloseAttributeWindow);
	

	AuraEnhancedInput->BindAbilityActions(InputData, this, &AAuraController::AbilityTagOnPressed, &AAuraController::AbilityTagOnTriggered, &AAuraController::AbilityTagOnReleased);

}

//Move Aura in Direction of Controller view
void AAuraController::MoveAura(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>()) 
	{
		ControlledPawn->AddMovementInput(ForwardVector, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightVector, MovementVector.X);

	}
}

void AAuraController::OpenCloseAttributeWindow()
{
	AAuraHUD* HUD = GetHUD<AAuraHUD>();
	if (!HUD) return;

	int32 ViewportX;
	int32 ViewportY;
	GetViewportSize(ViewportX,ViewportY);
	FVector2D ViewportSize = FVector2D(ViewportX, ViewportY);
	HUD->InteractWithAttributeOverlay(ViewportSize);
}

void AAuraController::ShiftPressed()
{
	bIsShiftDown = true;
}

void AAuraController::ShiftReleased()
{
	bIsShiftDown = false;
}

void AAuraController::TraceMouseCursor()
{

	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);
	if (CursorHit.bBlockingHit)
	{
		LastHitActor = CurrentHitActor;
		CurrentHitActor = Cast<ITargetInterface>(CursorHit.GetActor());

		{
			if (CurrentHitActor != LastHitActor)
			{
				if (LastHitActor)LastHitActor->StopHighlight();
				if (CurrentHitActor)CurrentHitActor->HighlightActor();
			}
		}
	}
}

void AAuraController::AbilityTagOnPressed(FGameplayTag InputTag)
{
	if(InputTag.MatchesTagExact(FAuraGameplayTags::Get().Input_LMB))
	{
	bTarget = CurrentHitActor ? true : false;
	bAutoRunning = false;
	}
}

void AAuraController::AbilityTagOnReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().Input_LMB))
	{
		if (GetAuraASC() != nullptr) GetAuraASC()->AbilityInputTagReleased(InputTag);
		return;
	}

	if (GetAuraASC() != nullptr) GetAuraASC()->AbilityInputTagReleased(InputTag);


	if (!bTarget && !bIsShiftDown)
	{
		
		APawn* CurrentPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && CurrentPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(CurrentPawn, CurrentPawn->GetActorLocation(), CachedDestination))
			{
				PathSpline->ClearSplinePoints();

				for (const auto& NavPoint : NavPath->PathPoints) 
				{
					PathSpline->AddSplinePoint(NavPoint, ESplineCoordinateSpace::World);
				}
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
				bAutoRunning = true;

			}
		}
		FollowTime = 0.f;
		bTarget = false;
	}
	
}

void AAuraController::AbilityTagOnTriggered(FGameplayTag InputTag)
{

	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().Input_LMB))
	{
		if (GetAuraASC() != nullptr) GetAuraASC()->AbilityInputTagHeld(InputTag);
		return;
	}

	if (bTarget || bIsShiftDown)
	{
		if (GetAuraASC() != nullptr) GetAuraASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		if (CursorHit.bBlockingHit)
		{
			CachedDestination = CursorHit.ImpactPoint;
		}
		if (APawn* CurrentPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - CurrentPawn->GetActorLocation()).GetSafeNormal2D();
			CurrentPawn->AddMovementInput(WorldDirection);
		}
	}
	
}

UMasterAbilityComponent* AAuraController::GetAuraASC()
{
	if (ASC == nullptr)
	{
		ASC = Cast <UMasterAbilityComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}

	return	ASC;
}
