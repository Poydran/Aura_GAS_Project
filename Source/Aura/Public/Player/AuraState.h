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
	const float GetPlayerLevel() const { return PlayerLevel; }
	void SetPlayerLevel(float NewLevel) { PlayerLevel = NewLevel; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	//AbilitySystem Components
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_PlayerLevel)
	float PlayerLevel = 1.f;
	
	UFUNCTION()
	void OnRep_PlayerLevel(float OldLevel);
};
