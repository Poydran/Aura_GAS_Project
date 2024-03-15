// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ClassInfoAsset.generated.h"

/**
 * 
 */

class UGameplayEffect;

UENUM(BlueprintType)
enum class EClassTypes : uint8
{

	ECC_Mage UMETA(DisplayName = "Mage"),
	ECC_Warrior UMETA(DisplayName = "Warrior"),
	ECC_Ranger UMETA(DisplayName = "Ranger")

};

USTRUCT(BlueprintType)
struct FCharacterClassesDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributesGE;

};


UCLASS()
class AURA_API UClassInfoAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TMap<EClassTypes, FCharacterClassesDefaultInfo> CharacterClassMap;

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributesGE;

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributesGE;

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TArray<TSubclassOf<class UGameplayAbility>> DefaultEnemyAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Common Class Defaults")
	TObjectPtr<UCurveTable> DamageCoefficients;

	FCharacterClassesDefaultInfo GetCharacterInfo(EClassTypes ClassType) const;


};
