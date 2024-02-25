// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability/AuraAttributeSet.h"
#include "Ability/Data/AttributeInfoAsset.h"
#include "AuraGameplayTags.h"
#include "UI/AttributeWidgetController.h"

void UAttributeWidgetController::BroadcastInitialWidgetValues()
{
	UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfoAsset);

	for (auto& MapEntry : AuraAS->TagsToAttributesMap)
	{
		FAttributeInfo Info = AttributeInfoAsset->FindAttributeInfoforTag(MapEntry.Key);
		FGameplayAttribute Attribute = MapEntry.Value();
		Info.AttributeValue = Attribute.GetNumericValue(AuraAS);
		AttributeInfoBroadcast.Broadcast(Info);
	}


	
	
	
}

void UAttributeWidgetController::BindCallbacksToDataSources()
{
	UAuraAttributeSet* AuraAS = CastChecked<UAuraAttributeSet>(AttributeSet);

	for (auto& MapEntry : AuraAS->TagsToAttributesMap){
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(MapEntry.Value()).AddLambda(
		[this,MapEntry,AuraAS] (const FOnAttributeChangeData& Data) 
			{
				FAttributeInfo Info = AttributeInfoAsset->FindAttributeInfoforTag(MapEntry.Key);
				FGameplayAttribute Attribute = MapEntry.Value();
				Info.AttributeValue = Attribute.GetNumericValue(AuraAS);
				AttributeInfoBroadcast.Broadcast(Info);
			}
		
		);
	}
}
