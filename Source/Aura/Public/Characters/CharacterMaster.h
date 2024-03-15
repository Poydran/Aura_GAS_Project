// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatInterface.h"
#include "CharacterMaster.generated.h"

//FWD
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class AURA_API ACharacterMaster : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterMaster();
	void EnableWeaponCustomDepth();
	void DisableWeaponCustomDepth();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die() override;

	UFUNCTION(NetMulticast, Reliable, Category = "Character|Death")
	virtual void MulticastHandleDeath();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//AbilitySystem Components
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void SetupGASonAura();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffects")
	TSubclassOf<class UGameplayEffect> PrimaryInitializer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffects")
	TSubclassOf<class UGameplayEffect> SecondaryInitializer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffects")
	TSubclassOf<class UGameplayEffect> VitalInitializer;

	virtual void InitDefaultAttributes() const;
	void SelfApplyGameplayEffectProcess(TSubclassOf<class UGameplayEffect> AttributeInitializer) const;

	void AddCharacterAbilities();

	virtual FVector ReturnWeaponSocket() override;

	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent, Category = "Character|Death")
	void StartDissolve(UMaterialInstanceDynamic* DynamicMaterialInstance);
	UFUNCTION(BlueprintImplementableEvent, Category = "Character|Death")
	void StartDissolveWeapon(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UPROPERTY(EditAnywhere, Category = "Character|Material")
	TObjectPtr<UMaterialInstance> DissolveMaterialInst; 
	UPROPERTY(EditAnywhere, Category = "Character|Material")
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInst;

private:

	UPROPERTY(EditAnywhere, Category = Combat)
	TObjectPtr<USkeletalMeshComponent> Weapon;


	UPROPERTY(EditAnywhere, Category = Combat)
	FName WeaponTipSocketName;

	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
};
