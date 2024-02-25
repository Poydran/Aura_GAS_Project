// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraHUD.h"
#include "Player/AuraController.h"
#include "Player/AuraState.h"
#include "AbilitySystemComponent.h"

#include "Ability/MasterAbilityComponent.h"
#include "Characters/Aura/AuraMaster.h"

AAuraMaster::AAuraMaster()
{
	
	AuraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Springarm"));
	AuraSpringArm->SetupAttachment(GetRootComponent());
	AuraSpringArm->bInheritPitch = false;
	AuraSpringArm->bInheritRoll = false;
	AuraSpringArm->bInheritYaw = false;

	AuraCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	AuraCamera->SetupAttachment(AuraSpringArm);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->bConstrainToPlane = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraMaster::SetupGASonAura()
{

	
	AAuraState* AuraPlayerState = GetPlayerState<AAuraState>();
	if (AuraPlayerState) 
	{
		AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
		AbilitySystem = AuraPlayerState->GetAbilitySystemComponent();
		AttributeSet = AuraPlayerState->GetAttributeSet();
		auto AuraASC =	Cast<UMasterAbilityComponent>(AbilitySystem);
		AuraASC->AbilityActorInfoSet();

		if (AAuraController* AuraController = Cast<AAuraController>(GetController())) 
		{
			if(AAuraHUD* AuraHUD = AuraController->GetHUD<AAuraHUD>()) AuraHUD->InitOverlay(AuraController, AuraPlayerState, AbilitySystem, AttributeSet);
		}

		InitNonVitalAttributes();
		AddCharacterAbilities();

	}
	else 
	{
		GetWorldTimerManager().SetTimer(ValidationTimer, this, &AAuraMaster::SetupGASonAura, .1f);
	}
	

}
const float AAuraMaster::GetCombatantLevel()
{

	if(AAuraState* AuraPlayerState = GetPlayerState<AAuraState>()) return AuraPlayerState->GetPlayerLevel();

	return 0.f  ;
}
void AAuraMaster::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//Setzt die AbilitySystemComponent on Server Site und die Variablen zu GAS auch
	SetupGASonAura();

}

void AAuraMaster::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//Setzt die AbilitySystemComponent on Client Site und die Variablen zu GAS auch
	SetupGASonAura();
}




