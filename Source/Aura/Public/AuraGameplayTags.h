// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "CoreMinimal.h"

/**
 * 
 */

struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return GameplayTags; };
	static void InitializeAuraGameplayTag();

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPierce;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_ManaRegen;
	FGameplayTag Attributes_Secondary_HealthRegen;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CritResi;
	FGameplayTag Attributes_Secondary_CritRate;
	FGameplayTag Attributes_Secondary_CritDamage;

	FGameplayTag Attributes_Primary_Vigor;
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resillience;

	FGameplayTag Input_RMB;
	FGameplayTag Input_LMB;
	FGameplayTag Input_key1;
	FGameplayTag Input_key2;
	FGameplayTag Input_key3;
	FGameplayTag Input_key4;
	FGameplayTag Input_key5;
	FGameplayTag Input_key6;
	FGameplayTag Input_key7;
	FGameplayTag Input_key8;
	FGameplayTag Input_key9;
protected:



private:
	static FAuraGameplayTags GameplayTags;
};

