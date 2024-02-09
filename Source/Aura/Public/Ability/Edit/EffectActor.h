// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class AURA_API AEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectActor();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffect(AActor* Target, TSubclassOf<UGameplayEffect> EffectClass);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StatusEffects)
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

private:

};
