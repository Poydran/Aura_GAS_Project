// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterMaster.h"
#include "Interfaces/TargetInterface.h"
#include "EnemyMaster.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AEnemyMaster : public ACharacterMaster, public ITargetInterface
{
	GENERATED_BODY()


public:
	AEnemyMaster();
	virtual void HighlightActor() override;
	virtual void StopHighlight() override;

protected:
	virtual void BeginPlay() override;
	
};
