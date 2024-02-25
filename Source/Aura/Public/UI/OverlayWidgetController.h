// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
/**
 * 
 */

USTRUCT(BlueprintType)
struct FWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UWidgetMaster> MessageWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, const FWidgetRow&, MessageRow);

UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UWidgetController
{
	GENERATED_BODY()

public:

	virtual void BroadcastInitialWidgetValues() override;
	virtual void BindCallbacksToDataSources() override;

	

	UPROPERTY(BlueprintAssignable, Category = "GAS|AttributeUpdate")
	FOnAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|AttributeUpdate")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|AttributeUpdate")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|AttributeUpdate")
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|MessageUpdate")
	FMessageWidgetRowSignature NewMessageRow;


protected:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<UDataTable> WidgetMessageDataTable;

	template<typename T>
	T* GetDataTableRowByTag(UDataTable* Datatable, const FGameplayTag& TagToSearch);
	
};

template<typename T>
inline T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* Datatable, const FGameplayTag& TagToSearch)
{
	return Datatable->FindRow<T>(TagToSearch.GetTagName(), TEXT(""));
	
}
