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

UCLASS()
class AURA_API AAuraController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraController();

	virtual void PlayerTick(float DeltaTime) override;

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

	//UIActions
	UPROPERTY(EditAnywhere, Category = UI)
	TObjectPtr<UInputAction> IAAttributeOverlay;

	//Mouse Hover Targets for highlighting Actor
	ITargetInterface* CurrentHitActor;
	ITargetInterface* LastHitActor;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputDataAsset> InputData;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMasterAbilityComponent> ASC;

	//Funktionen

	//Move Aura in X and Y Directions
	UFUNCTION()
	void MoveAura(const FInputActionValue& Value);

	void OpenCloseAttributeWindow();


	//Trace for Actor under MouseCursor
	void TraceMouseCursor();

	void AbilityTagOnPressed(FGameplayTag InputTag);
	void AbilityTagOnReleased(FGameplayTag InputTag);
	void AbilityTagOnTriggered(FGameplayTag InputTag);

	UMasterAbilityComponent* GetAuraASC();
};
