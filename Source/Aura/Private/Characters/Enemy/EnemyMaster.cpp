// Fill out your copyright notice in the Description page of Project Settings.

#include "Aura/Aura.h"
#include "Ability/MasterAbilityComponent.h"
#include "Ability/AuraAttributeSet.h"
#include "Ability/MasterAbilityComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/WidgetMaster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AuraGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Ability/AuraAbilitySystemFunctionLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Characters/Enemy/MasterAIController.h"
#include "Characters/Enemy/EnemyMaster.h"



AEnemyMaster::AEnemyMaster()
{
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_STENCIL_RED);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	AbilitySystem = CreateDefaultSubobject<UMasterAbilityComponent>(TEXT("EnemyAbilities"));
	AbilitySystem->SetIsReplicated(true);
	AbilitySystem->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>(TEXT("EnemyAttributes"));

	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidgetComponent->SetupAttachment(GetRootComponent());



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

void AEnemyMaster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	AIController = CastChecked<AMasterAIController>(NewController);

	AIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	AIController->RunBehaviorTree(BehaviorTree);
}

const float AEnemyMaster::GetCombatantLevel()
{
	return Level;
}


void AEnemyMaster::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewTagCount)
{
	 bShouldReact = NewTagCount > 0;
	 GetCharacterMovement()->MaxWalkSpeed = bShouldReact ? 0.f : BaseWalkSpeed;


}

void AEnemyMaster::Die()
{
	Super::Die();
	SetLifeSpan(DeathDespawnTime);
}

void AEnemyMaster::BeginPlay()
{
	Super::BeginPlay();
	
	SetupGASonAura();
	
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;

	if (UWidgetMaster* UserWidget = Cast < UWidgetMaster >(HealthBarWidgetComponent->GetUserWidgetObject()))
	{
		UserWidget->SetWidgetController(this);
	}

	UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);
	AbilitySystem->GetGameplayAttributeValueChangeDelegate(AuraAS->GetHealthAttribute()).AddLambda(

		[this](const FOnAttributeChangeData& Data) {

			HealthChange.Broadcast(Data.NewValue);
		}
	);
	AbilitySystem->GetGameplayAttributeValueChangeDelegate(AuraAS->GetMaxHealthAttribute()).AddLambda(

		[this](const FOnAttributeChangeData& Data) {

			MaxHealthChange.Broadcast(Data.NewValue);
		}
	);

	if(HasAuthority()) UAuraAbilitySystemFunctionLibrary::GiveStartupAbilities(this, AbilitySystem);
	
	
	AbilitySystem->RegisterGameplayTagEvent(FAuraGameplayTags::Get().HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &AEnemyMaster::HitReactTagChanged);

	MaxHealthChange.Broadcast(AuraAS->GetMaxHealth());
	HealthChange.Broadcast(AuraAS->GetHealth());

	//UE_LOG(LogTemp, Warning, TEXT("HealthValue %f and Name %s"), AuraAS->GetHealth());

}

void AEnemyMaster::SetupGASonAura()
{
	AbilitySystem->InitAbilityActorInfo(this, this);
	auto EnemyASC = Cast<UMasterAbilityComponent>(AbilitySystem);
	EnemyASC->AbilityActorInfoSet();

	if(HasAuthority()) InitDefaultAttributes();
	
	
}

void AEnemyMaster::InitDefaultAttributes() const
{
	UAuraAbilitySystemFunctionLibrary::InitEnemyAttributes(this, EnemyClassType, Level, AbilitySystem);
}
