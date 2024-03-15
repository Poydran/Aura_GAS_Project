// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemy/MasterAIController.h"

AMasterAIController::AMasterAIController()
{

	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	check(Blackboard);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	check(BehaviorTreeComponent);
}
