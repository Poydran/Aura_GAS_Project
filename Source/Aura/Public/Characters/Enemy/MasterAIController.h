// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MasterAIController.generated.h"

/**
 * 
 */

class UBehaviorTreeComponent;

UCLASS()
class AURA_API AMasterAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMasterAIController();


protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	
};
