// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayTagsManager.h"
#include "AuraGameplayTags.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeAuraGameplayTag()
{
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("reduces damage taken"));
	GameplayTags.Attributes_Secondary_ArmorPierce = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPierce"), FString("lets you deal more damage against armor"));
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"), FString("gives you a chance to block incoming damage"));
	GameplayTags.Attributes_Secondary_CritDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CritDamage"), FString("damage multiplier for critical hits"));
	GameplayTags.Attributes_Secondary_CritRate = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CritRate"), FString("increases chance for a critical hit"));
	GameplayTags.Attributes_Secondary_CritResi = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CritResi"), FString("increases resistance to critical hits"));
	GameplayTags.Attributes_Secondary_HealthRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegen"), FString("how fast health is regenerating"));
	GameplayTags.Attributes_Secondary_ManaRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegen"), FString("how fast mana is regenerating"));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("the maximum value of health"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("the maximum value of Mana"));

	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("increases Health related Attributes"));
	GameplayTags.Attributes_Primary_Resillience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resillience"), FString("increases Armor related Attributes"));
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("increases Damage and Crit related Attributes"));
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("increases Mana and crit related Attributes"));

	GameplayTags.Input_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.RMB"), FString("InputAction for Right Mouse Button"));
	GameplayTags.Input_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.LMB"), FString("InputAction for Left Mouse Button"));
	GameplayTags.Input_key1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.key1"), FString("InputAction for Number key 1"));
	GameplayTags.Input_key2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.key2"), FString("InputAction for Number key 2"));
	GameplayTags.Input_key3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.key3"), FString("InputAction for Number key 3"));
	GameplayTags.Input_key4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.key4"), FString("InputAction for Number key 4"));
	GameplayTags.Input_key5 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.key5"), FString("InputAction for Number key 5"));
	GameplayTags.Input_key6 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.key6"), FString("InputAction for Number key 6"));
	GameplayTags.Input_key7 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.key7"), FString("InputAction for Number key 7"));
	GameplayTags.Input_key8 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.key8"), FString("InputAction for Number key 8"));
	GameplayTags.Input_key9 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.key9"), FString("InputAction for Number key 9"));
}
