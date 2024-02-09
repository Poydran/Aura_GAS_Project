// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraController.generated.h"

/**
 * 
 * 
 */
class UInputAction;
struct FInputActionValue;
class ITargetInterface;

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

	//Mouse Hover Targets for highlighting Actor
	ITargetInterface* CurrentHitActor;
	ITargetInterface* LastHitActor;

	//Funktionen

	//Move Aura in X and Y Directions
	UFUNCTION()
	void MoveAura(const FInputActionValue& Value);

	//Trace for Actor under MouseCursor
	void TraceMouseCursor();

	
};
