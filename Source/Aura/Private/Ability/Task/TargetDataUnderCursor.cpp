// Fill out your copyright notice in the Description page of Project Settings.

#include "Interfaces/TargetInterface.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "AbilitySystemComponent.h"
#include "Ability/Task/TargetDataUnderCursor.h"

UTargetDataUnderCursor* UTargetDataUnderCursor::GetTargetDataUnderCursor(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderCursor* MyTask = NewAbilityTask<UTargetDataUnderCursor>(OwningAbility);
	return MyTask;
}

void UTargetDataUnderCursor::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& TargetHandle, FGameplayTag TargetDataTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		TargetData.Broadcast(TargetHandle);
	}

}

void UTargetDataUnderCursor::Activate()
{

	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	if (bIsLocallyControlled)
	{
		SendCursorData();
	}
	else 
	{
		AbilitySystemComponent->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(), GetActivationPredictionKey()).AddUObject(this, &UTargetDataUnderCursor::OnTargetDataReplicatedCallback);
		const bool bCalledDelegate = AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(), GetActivationPredictionKey());
		if (!bCalledDelegate) {
			SetWaitingOnRemotePlayerData();
		}
	}

}

void UTargetDataUnderCursor::SendCursorData()
{

	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	if (!PlayerController) return;

	FGameplayAbilityTargetDataHandle TargetDataHandle;
	FHitResult TargetHit;
	PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, TargetHit);


	//TargetLocation.Broadcast(TargetHit.ImpactPoint);
	Data->HitResult = TargetHit;
	TargetDataHandle.Add(Data);

	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), TargetDataHandle, FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey);

	//Checks if Ability is Still active and its safe to broadcast the AbilityTask
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		TargetData.Broadcast(TargetDataHandle);
	}



}
