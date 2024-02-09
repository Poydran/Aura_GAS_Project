// Fill out your copyright notice in the Description page of Project Settings.

#include "Aura/Aura.h"
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


