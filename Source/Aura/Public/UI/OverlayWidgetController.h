// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, UpdateHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, UpdateMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, UpdateMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, UpdateMaxMana);

UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UWidgetController
{
	GENERATED_BODY()

public:

	virtual void BroadcastInitialWidgetValues() override;
	virtual void BindCallbacksToDataSources() override;

	void OnHealthUpdate(const FOnAttributeChangeData& UpdateData);

	void OnMaxHealthUpdate(const FOnAttributeChangeData& UpdateData);

	void OnManaUpdate(const FOnAttributeChangeData& UpdateData);

	void OnMaxManaUpdate(const FOnAttributeChangeData& UpdateData);

	UPROPERTY(BlueprintAssignable, Category = "GAS|AttributeUpdate")
	FOnHealthChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|AttributeUpdate")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|AttributeUpdate")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|AttributeUpdate")
	FOnMaxManaChangedSignature OnMaxManaChanged;

};
