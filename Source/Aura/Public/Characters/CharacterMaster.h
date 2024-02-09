// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CharacterMaster.generated.h"

//FWD
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class AURA_API ACharacterMaster : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterMaster();
	void EnableWeaponCustomDepth();
	void DisableWeaponCustomDepth();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//AbilitySystem Components
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;


private:

	UPROPERTY(EditAnywhere, Category = Combat)
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
