// Fill out your copyright notice in the Description page of Project Settings.

#include "EnhancedInputSubsystems.h"
#include "Input/AuraEnhancedInputComponent.h"
#include "Interfaces/TargetInterface.h"
#include "Player/AuraHUD.h"
#include "Ability/MasterAbilityComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Player/AuraController.h"

AAuraController::AAuraController()
{
	bReplicates = true;
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
}

//Setup InputComponent and Actions
void AAuraController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraEnhancedInputComponent* AuraEnhancedInput = CastChecked<UAuraEnhancedInputComponent>(InputComponent);
	AuraEnhancedInput->BindAction(IAMove, ETriggerEvent::Triggered, this, &AAuraController::MoveAura);
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

void AAuraController::TraceMouseCursor()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	if (HitResult.bBlockingHit) 
	{
		LastHitActor = CurrentHitActor;
		CurrentHitActor = Cast<ITargetInterface>(HitResult.GetActor());

		/*
			LineTrace From Cursor to Actor with following scenarios:

			1. LastHitActor && CurrentHitActor == Null
				-- Do nothing
			2. LastHitActor == Null && CurrentHitActor == Valid
				-- Call Highlight function on CurrentHitActor
			3. LastHitActor == Valid && CurrentHitActor == Null
				-- Call StopHighlight function on LastHitActor
			4. LastHitActor == Valid && CurrentHitActor == Valid, both are the same Actor
				-- Do nothing
			5. LastHitActor == Valid && CurrentHitActor == Valid, both are the different Actors
				-- Call Highlight function on CurrentHitActor and StopHighlight function on LastHitActor
		*/
		if (!LastHitActor)
		{
			if (CurrentHitActor)
			{
				// Case 2
				CurrentHitActor->HighlightActor();
		
			}
			else 
			{
				// Case 1
			}
		}
		else //LastHitActor is Valid Case 3-5
		{
			if (CurrentHitActor) 
			{
				if(CurrentHitActor == LastHitActor) 
				{
					//Case 5 both are the same
				}
				else 
				{
					//Case 4 both are different Actors
					LastHitActor->StopHighlight();
					CurrentHitActor->HighlightActor();
				}
			}
			else
			{
				//Case 3 
				LastHitActor->StopHighlight();
			}
		}	
	}
}

void AAuraController::AbilityTagOnPressed(FGameplayTag InputTag)
{
}

void AAuraController::AbilityTagOnReleased(FGameplayTag InputTag)
{
	if (GetAuraASC() == nullptr) return;
	GetAuraASC()->AbilityInputTagReleased(InputTag);
}

void AAuraController::AbilityTagOnTriggered(FGameplayTag InputTag)
{
	if (GetAuraASC() == nullptr) return;
	GetAuraASC()->AbilityInputTagHeld(InputTag);
}

UMasterAbilityComponent* AAuraController::GetAuraASC()
{
	if (ASC == nullptr)
	{
		ASC = Cast <UMasterAbilityComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}

	return	ASC;
}
