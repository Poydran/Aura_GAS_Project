// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetController.generated.h"

/**
 * 
 */
class UAttributeSet;
class UAbilitySystemComponent;



USTRUCT(BlueprintType)
struct FDataSources
{
	GENERATED_BODY()
	
	FDataSources() {}
	FDataSources(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS) 
		: Playercontroller(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> Playercontroller = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;

};



UCLASS()
class AURA_API UWidgetController : public UObject
{
	GENERATED_BODY()



public:

	UFUNCTION(BlueprintCallable)
	void SetDataSources(const FDataSources& DataSources);
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialWidgetValues();
	virtual void BindCallbacksToDataSources();

protected:


	//Data Sources to Broadcast from; Target = Widgets /start
	UPROPERTY(BlueprintReadOnly, Category = WidgetController)
	TObjectPtr<APlayerController> Playercontroller;

	UPROPERTY(BlueprintReadOnly, Category = WidgetController)
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = WidgetController)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComp;

	UPROPERTY(BlueprintReadOnly, Category = WidgetController)
	TObjectPtr<UAttributeSet> AttributeSet;
	//Data Sources to Broadcast from; Target = Widgets /end

};
