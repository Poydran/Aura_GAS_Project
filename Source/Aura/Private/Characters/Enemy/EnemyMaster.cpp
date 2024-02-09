// Fill out your copyright notice in the Description page of Project Settings.

#include "Aura/Aura.h"
#include "Ability/MasterAbilityComponent.h"
#include "Ability/AuraAttributeSet.h"
#include "Characters/Enemy/EnemyMaster.h"



AEnemyMaster::AEnemyMaster()
{
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_STENCIL_RED);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	AbilitySystem = CreateDefaultSubobject<UMasterAbilityComponent>(TEXT("EnemyAbilities"));
	AbilitySystem->SetIsReplicated(true);
	AbilitySystem->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("EnemyAttributes"));

}

void AEnemyMaster::HighlightActor()
{
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, .3, FColor::Cyan, GetName());
	}
	*/
	GetMesh()->SetRenderCustomDepth(true);
	EnableWeaponCustomDepth();
	

}

void AEnemyMaster::StopHighlight()
{
	GetMesh()->SetRenderCustomDepth(false);
	DisableWeaponCustomDepth();
}

void AEnemyMaster::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystem->InitAbilityActorInfo(this, this);
}
