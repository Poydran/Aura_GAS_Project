// Fill out your copyright notice in the Description page of Project Settings.

#include "AuraAbilityTypes.h"
#include "Ability/AuraAbilitySystemGlobals.h"

FGameplayEffectContext* UAuraAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAuraGameplayEffectContext();
}
