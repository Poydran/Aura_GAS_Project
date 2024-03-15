// Fill out your copyright notice in the Description page of Project Settings.

#include "Aura/Aura.h"
#include "AbilitySystemComponent.h"
#include "Ability/MasterAbilityComponent.h"
#include "Components/CapsuleComponent.h"
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
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

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

UAnimMontage* ACharacterMaster::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void ACharacterMaster::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	MulticastHandleDeath();
}

void ACharacterMaster::MulticastHandleDeath_Implementation()
{
	Weapon->SetEnableGravity(true);
	Weapon->SetSimulatePhysics(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Dissolve();
}

// Called when the game starts or when spawned
void ACharacterMaster::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterMaster::SetupGASonAura()
{
}

void ACharacterMaster::InitDefaultAttributes() const
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

void ACharacterMaster::Dissolve()
{
	if (IsValid(DissolveMaterialInst))
	{
		UMaterialInstanceDynamic* DynamicMI = UMaterialInstanceDynamic::Create(DissolveMaterialInst, this);
		GetMesh()->SetMaterial(0, DynamicMI);
		StartDissolve(DynamicMI);
	}
	if (IsValid(WeaponDissolveMaterialInst))
	{
		UMaterialInstanceDynamic* DynamicMI = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInst, this);
		Weapon->SetMaterial(0, DynamicMI);
		StartDissolveWeapon(DynamicMI);

	}
}
