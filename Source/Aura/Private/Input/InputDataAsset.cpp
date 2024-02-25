// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputDataAsset.h"

const UInputAction* UInputDataAsset::FindInputActionByTag(const FGameplayTag& GameplayTag, bool bTagNotFound) const
{

	for (const auto& InputTag : InputTagData) 
	{
		if (GameplayTag.MatchesTagExact(InputTag.AbilityTag)) return InputTag.InputAction;

	}
	if (bTagNotFound) 
	{
		UE_LOG(LogTemp, Error, TEXT("No InputAction found for Tag: %s"), *GameplayTag.ToString());
	}

	return nullptr;
}
