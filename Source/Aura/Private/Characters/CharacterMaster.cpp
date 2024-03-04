// Fill out your copyright notice in the Description page of Project Settings.

#include "Aura/Aura.h"
#include "AbilitySystemComponent.h"
#include "Ability/MasterAbilityComponent.h"
#include "Characters/CharacterMaster.h"

// Sets default values
ACharacterMaster::ACharacterMaster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName("WeaponSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Weapon->SetCustomDepthStencilValue(CUSTOM_STENCIL_RED);

}

void ACharacterMaster::EnableWeaponCustomDepth()
{
	Weapon->SetRenderCustomDepth(true);
}

void ACharacterMaster::DisableWeaponCustomDepth()
{
	Weapon->SetRenderCustomDepth(false);
}

UAbilitySystemComponent* ACharacterMaster::GetAbilitySystemComponent() const
{
	return AbilitySystem;

}

// Called when the game starts or when spawned
void ACharacterMaster::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterMaster::SetupGASonAura()
{
}

void ACharacterMaster::InitNonVitalAttributes() const
{
	SelfApplyGameplayEffectProcess(PrimaryInitializer);
	SelfApplyGameplayEffectProcess(SecondaryInitializer);
	SelfApplyGameplayEffectProcess(VitalInitializer);
}



void ACharacterMaster::SelfApplyGameplayEffectProcess(TSubclassOf<class UGameplayEffect> AttributeInitializer) const
{
	check(GetAbilitySystemComponent() && AttributeInitializer);
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(AttributeInitializer, 1, EffectContextHandle);

	const auto ActiveSpecHandle = GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ACharacterMaster::AddCharacterAbilities()
{
	if (!HasAuthority()) return;
	if (StartupAbilities.IsEmpty()) return;

	CastChecked<UMasterAbilityComponent>(AbilitySystem)->GrantStartupAbilities(StartupAbilities);
	
	
}

FVector ACharacterMaster::ReturnWeaponSocket()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}
