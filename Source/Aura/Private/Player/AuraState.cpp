// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability/MasterAbilityComponent.h"
#include "Ability/AuraAttributeSet.h"
#include "Player/AuraState.h"

AAuraState::AAuraState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystem = CreateDefaultSubobject<UMasterAbilityComponent>(TEXT("EnemyAbilities"));
	AbilitySystem->SetIsReplicated(true);
	AbilitySystem->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("EnemyAttributes"));

}

UAbilitySystemComponent* AAuraState::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}
