// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterMaster.h"
#include "Interfaces/TargetInterface.h"
#include "UI/OverlayWidgetController.h"
#include "Ability/Data/ClassInfoAsset.h"
#include "EnemyMaster.generated.h"

/**
 * 
 */
class UBehaviorTree;
class AMasterAIController;


UCLASS()
class AURA_API AEnemyMaster : public ACharacterMaster, public ITargetInterface
{
	GENERATED_BODY()


public:
	AEnemyMaster();
	virtual void HighlightActor() override;
	virtual void StopHighlight() override;
	
	virtual void PossessedBy(AController* NewController) override;

	virtual const float GetCombatantLevel() override;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature HealthChange;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature MaxHealthChange;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewTagCount);

	virtual void Die() override;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bShouldReact = false;

	UPROPERTY(EditAnywhere, Category = "EnemyDefaults")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnemyDefaults")
	float DeathDespawnTime = 10.f;


protected:
	virtual void BeginPlay() override;

	virtual void SetupGASonAura() override;

	virtual void InitDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Level = 1.f;

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AMasterAIController> AIController;

	
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UWidgetComponent> HealthBarWidgetComponent;

	UPROPERTY(EditAnywhere, Category = "ClassType")
	EClassTypes EnemyClassType = EClassTypes::ECC_Mage;

	
};
