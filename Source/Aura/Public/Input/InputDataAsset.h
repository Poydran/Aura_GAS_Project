// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTags.h"
#include "InputDataAsset.generated.h"

/**
 * 
 */

class UInputAction;


USTRUCT(BlueprintType)
struct FInputTagMap
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AbilityTag = FGameplayTag() ;
};


UCLASS()
class AURA_API UInputDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FInputTagMap> InputTagData;

	const UInputAction* FindInputActionByTag(const FGameplayTag& GameplayTag, bool bTagNotFound = false) const;

};
