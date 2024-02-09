// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "EffectActor.generated.h"




UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	EAP_ApplyOnOverlap UMETA(DisplayName = "OnOverlap"),
	EAP_ApplyOnEndOverlap UMETA(DisplayName = "OnEndOverlap"),
	EAP_DoNotApply UMETA(DisplayName = "DoNotApply")

};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	ERP_RemoveOnOverlap UMETA(DisplayName = "OnOverlap"),
	ERP_RemoveOnEndOverlap UMETA(DisplayName = "OnEndOverlap"),
	ERP_DoNotRemove UMETA(DisplayName = "DoNotRemove")

};


class UGameplayEffect;
class UAbilitySytemComponent;

UCLASS()
class AURA_API AEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectActor();

	

protected:
	// Called when the game starts or when spawned


	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffect(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectClass);

	bool IsGameplayEffectInfinite(const FGameplayEffectSpecHandle& EffectSpecHandle);

	UFUNCTION(BlueprintCallable)
	void EndOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable)
	void BeginOverlap(AActor* TargetActor);

	void RemoveEffectOnTargetASC(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StatusEffects)
	bool bDestroyOnEffectRemoval = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StatusEffects)
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StatusEffects)
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StatusEffects)
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StatusEffects)
	EEffectApplicationPolicy InfiniteApplicationPolicy = EEffectApplicationPolicy::EAP_DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StatusEffects)
	EEffectApplicationPolicy InstantApplicationPolicy = EEffectApplicationPolicy::EAP_DoNotApply;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StatusEffects)
	EEffectApplicationPolicy DurationApplicationPolicy = EEffectApplicationPolicy::EAP_DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StatusEffects)
	EEffectRemovalPolicy InfiniteRemovalPolicy = EEffectRemovalPolicy::ERP_DoNotRemove;

private:

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> EffectHandleMap;

};
