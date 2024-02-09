// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AuraState.generated.h"

/**
 * 
 */
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AURA_API AAuraState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }


protected:
	//AbilitySystem Components
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
};
