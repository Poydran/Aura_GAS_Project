// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController.h"
#include "AttributeWidgetController.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoAssetBroadcastSignature, const struct FAttributeInfo& , AttributeInfo);



UCLASS(BlueprintType, Blueprintable)
class AURA_API UAttributeWidgetController : public UWidgetController
{
	GENERATED_BODY()
	
public:
	virtual void BroadcastInitialWidgetValues() override;
	virtual void BindCallbacksToDataSources() override;

	UPROPERTY(BlueprintAssignable, Category = "AttributeInfo|Delegate")
	FAttributeInfoAssetBroadcastSignature AttributeInfoBroadcast;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AttributeInfo|DataAsset")
	TObjectPtr<class UAttributeInfoAsset> AttributeInfoAsset;
};
