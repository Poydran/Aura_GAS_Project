// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Ability/Edit/EffectActor.h"

// Sets default values
AEffectActor::AEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));

}





void AEffectActor::ApplyGameplayEffect(AActor* Target, TSubclassOf<UGameplayEffect> EffectClass)
{
	checkf(EffectClass, TEXT("Die Effekt Klasse ist nicht gesetzt!"));
	UAbilitySystemComponent* TargetASC	= UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (TargetASC) {
		FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(EffectClass, 1.0f, EffectContextHandle);
		const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

		if (IsGameplayEffectInfinite(EffectSpecHandle) && InfiniteRemovalPolicy != EEffectRemovalPolicy::ERP_DoNotRemove) 
		{
			EffectHandleMap.Add(ActiveEffectHandle, TargetASC);
		}

	}
	else 
	{ 
		return; 
	}
	
}

bool AEffectActor::IsGameplayEffectInfinite(const FGameplayEffectSpecHandle& EffectSpecHandle)
{
	return EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
}

void AEffectActor::EndOverlap(AActor* TargetActor)
{
	if (InstantApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnEndOverlap)
	{
		ApplyGameplayEffect(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnEndOverlap) 
	{
		ApplyGameplayEffect(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnEndOverlap)
	{
		ApplyGameplayEffect(TargetActor, InfiniteGameplayEffectClass);
	}
	if (InfiniteRemovalPolicy == EEffectRemovalPolicy::ERP_RemoveOnEndOverlap)
	{
		RemoveEffectOnTargetASC(TargetActor);
	}
}

void AEffectActor::BeginOverlap(AActor* TargetActor)
{
	if (InstantApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnOverlap) 
	{
		ApplyGameplayEffect(TargetActor, InstantGameplayEffectClass);
	}
	if (DurationApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnOverlap)
	{
		ApplyGameplayEffect(TargetActor, DurationGameplayEffectClass);
	}
	if (InfiniteApplicationPolicy == EEffectApplicationPolicy::EAP_ApplyOnOverlap)
	{
		ApplyGameplayEffect(TargetActor, InfiniteGameplayEffectClass);
	}
	if (InfiniteRemovalPolicy == EEffectRemovalPolicy::ERP_RemoveOnOverlap)
	{
		RemoveEffectOnTargetASC(TargetActor);
	}
}

void AEffectActor::RemoveEffectOnTargetASC(AActor* TargetActor)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC)
	{
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (auto HandlePair : EffectHandleMap)
		{
			if (HandlePair.Value == TargetASC) HandlesToRemove.Add(HandlePair.Key);
		}
		for (auto Handle : HandlesToRemove)
		{
			TargetASC->RemoveActiveGameplayEffect(Handle, 1);
			EffectHandleMap.FindAndRemoveChecked(Handle);
		}
	}
}

