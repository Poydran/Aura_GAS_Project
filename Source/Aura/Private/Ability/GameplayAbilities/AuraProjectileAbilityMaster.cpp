// Fill out your copyright notice in the Description page of Project Settings.

#include "Interfaces/CombatInterface.h"
#include "Ability/Edit/AuraProjectile.h"
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
		SpawnProjectile->FinishSpawning(SpawnTransform);
	}
}
