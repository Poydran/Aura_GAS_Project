// Fill out your copyright notice in the Description page of Project Settings.

#include "AuraGameplayTags.h"
#include "AbilitySystemGlobals.h"
#include "AuraAssetManager.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	
	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitializeAuraGameplayTag();

	//Required to use targetdata
	UAbilitySystemGlobals::Get().InitGlobalData();
}
