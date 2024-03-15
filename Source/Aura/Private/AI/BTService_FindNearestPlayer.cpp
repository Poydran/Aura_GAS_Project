// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "AI/BTService_FindNearestPlayer.h"

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	APawn* OwningPawn = AIOwner->GetPawn();

	const FName TargetTag = OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");

	TArray<AActor*> TargetActors;
	UGameplayStatics::GetAllActorsWithTag(OwningPawn, TargetTag, TargetActors);


	if (TargetActors.IsEmpty()) return;
	const FVector OwnerLocation = OwningPawn->GetActorLocation();
	AActor* FinalTarget = nullptr;
	float FinalDistance = TNumericLimits<float>::Max();
	for (AActor* Target : TargetActors)
	{
		const FVector TargetLocation = Target->GetActorLocation();

		float Distance = (TargetLocation - OwnerLocation).Length();
		
		if (FinalDistance > Distance)
		{
			FinalDistance = Distance;
			FinalTarget = Target;
		}
	}
	UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetToFollow, FinalTarget);
	UBTFunctionLibrary::SetBlackboardValueAsFloat(this, DistanceToTarget, FinalDistance);

}
