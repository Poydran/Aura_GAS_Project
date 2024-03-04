// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/GameplayAbilities/AuraGameplayAbility.h"
#include "AuraProjectileAbilityMaster.generated.h"

class AAuraProjectile;

UCLASS()
class AURA_API UAuraProjectileAbilityMaster : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<AAuraProjectile> ProjectileToSpawn;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectileFromBP(const FVector& TargetLocation);
};
