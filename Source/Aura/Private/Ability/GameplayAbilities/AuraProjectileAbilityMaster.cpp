// Fill out your copyright notice in the Description page of Project Settings.

#include "Interfaces/CombatInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Ability/Edit/AuraProjectile.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "Ability/GameplayAbilities/AuraProjectileAbilityMaster.h"

void UAuraProjectileAbilityMaster::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UAuraProjectileAbilityMaster::SpawnProjectileFromBP(const FVector& TargetLocation)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();

	if (!bIsServer) return;

	
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SpawnLocation = CombatInterface->ReturnWeaponSocket();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SpawnLocation);
		FRotator ProjectileRotation = (TargetLocation - SpawnLocation).Rotation();
		SpawnTransform.SetRotation(ProjectileRotation.Quaternion());
		AAuraProjectile* SpawnProjectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileToSpawn, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		UAbilitySystemComponent* CauserASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());

		FGameplayEffectContextHandle ContextHandle = CauserASC->MakeEffectContext();
		ContextHandle.SetAbility(this);
		ContextHandle.AddSourceObject(SpawnProjectile);
		TArray<TWeakObjectPtr<AActor>> ActorsArray;
		ActorsArray.Add(SpawnProjectile);
		ContextHandle.AddActors(ActorsArray);
		FGameplayEffectSpecHandle DamageSpecHandle = CauserASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), ContextHandle);

		const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();


		for( auto& DamageType : DamageTypeMap)
		{ 

		const float ScaledDamage = DamageType.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, DamageType.Key, ScaledDamage);

		}

		SpawnProjectile->DamageEffectSpecHandle = DamageSpecHandle;
		SpawnProjectile->FinishSpawning(SpawnTransform);
	}
}
