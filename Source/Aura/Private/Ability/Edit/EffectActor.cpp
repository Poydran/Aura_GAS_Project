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



	



// Called when the game starts or when spawned
void AEffectActor::BeginPlay()
{
	Super::BeginPlay();

	
}

void AEffectActor::ApplyGameplayEffect(AActor* Target, TSubclassOf<UGameplayEffect> EffectClass)
{
	checkf(EffectClass, TEXT("Die Effekt Klasse ist nicht gesetzt!"));
	UAbilitySystemComponent* TargetASC	= UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if (TargetASC) {
		FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(EffectClass, 1.0f, EffectContextHandle);
		TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
	else 
	{ 
		return; 
	}
	
}

