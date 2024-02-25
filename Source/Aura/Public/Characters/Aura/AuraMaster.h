// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterMaster.h"
#include "AuraMaster.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraMaster : public ACharacterMaster
{
	GENERATED_BODY()
	
public:

	AAuraMaster();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupGASonAura() override;
	virtual const float GetCombatantLevel() override;


private:

	//Camera Components
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<class UCameraComponent> AuraCamera;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<class USpringArmComponent> AuraSpringArm;

	FTimerHandle ValidationTimer;
	

};
