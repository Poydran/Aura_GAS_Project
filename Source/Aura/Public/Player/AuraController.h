// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTags.h"
#include "AuraController.generated.h"


/**
 * 
 * 
 */
class UInputAction;
struct FInputActionValue;
class ITargetInterface;
class UInputDataAsset;
class UMasterAbilityComponent;
class USplineComponent;

UCLASS()
class AURA_API AAuraController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraController();

	virtual void PlayerTick(float DeltaTime) override;

	void AutoRun();

	UFUNCTION(Client,Reliable)
	void ShowDamageNumbers(float Damgage, AActor* TargetHit, bool bBlockedHit, bool bCriticalHit);
	

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;



private:

	//Variablen

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr< class UInputMappingContext> AuraContext;

	//InputActions
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> IAMove;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> IAShift;

	//UIActions
	UPROPERTY(EditAnywhere, Category = UI)
	TObjectPtr<UInputAction> IAAttributeOverlay;

	//Mouse Hover Targets for highlighting Actor
	ITargetInterface* CurrentHitActor;
	ITargetInterface* LastHitActor;

	//HitResult of MouseCursor Trace
	FHitResult CursorHit;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputDataAsset> InputData;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMasterAbilityComponent> ASC;

	//Click to Move /start
	FVector CachedDestination = FVector();

	float FollowTime = 0.f;

	float ShortPressThreshold = 0.5f;

	bool bAutoRunning = false;

	bool bTarget = false;

	bool bIsShiftDown = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> PathSpline;
	//Click to Move /end

	UPROPERTY(EditDefaultsOnly, Category = "UI|Widgets")
	TSubclassOf<class UAuraWidgetComponent> DamageWidgetComponent;

	//Funktionen

	//Move Aura in X and Y Directions
	UFUNCTION()
	void MoveAura(const FInputActionValue& Value);

	void OpenCloseAttributeWindow();

	void ShiftPressed();
	void ShiftReleased();


	//Trace for Actor under MouseCursor
	void TraceMouseCursor();

	void AbilityTagOnPressed(FGameplayTag InputTag);
	void AbilityTagOnReleased(FGameplayTag InputTag);
	void AbilityTagOnTriggered(FGameplayTag InputTag);

	UMasterAbilityComponent* GetAuraASC();
};
