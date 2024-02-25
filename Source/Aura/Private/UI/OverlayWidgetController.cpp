// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability/AuraAttributeSet.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"
#include "Ability/MasterAbilityComponent.h"
#include "UI/OverlayWidgetController.h"

void UOverlayWidgetController::BroadcastInitialWidgetValues()
{
	if (const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet))
	{ 
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	}
}

// wird im AuraHUD bei der Erstellung dieses OverlayController aufgerufen um die Update Funktion für Attribute an dieses zu binden 
void UOverlayWidgetController::BindCallbacksToDataSources()
{
	if (const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet))
	{
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
		[this] (const FOnAttributeChangeData& UpdateData) 
			{
				OnHealthChanged.Broadcast(UpdateData.NewValue);
			}
		);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& UpdateData)
			{
				OnMaxHealthChanged.Broadcast(UpdateData.NewValue);
			}
		);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& UpdateData)
			{
				OnManaChanged.Broadcast(UpdateData.NewValue);
			}
		);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& UpdateData)
			{
				OnMaxManaChanged.Broadcast(UpdateData.NewValue);
			}
		);

		Cast<UMasterAbilityComponent>(AbilitySystemComp)->EffectAssetTag.AddLambda(
			[this](const FGameplayTagContainer& AssetTags) {

				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName(TEXT("Message")));
				
				for (auto Tag : AssetTags) 
				{
					if (Tag.MatchesTag(MessageTag)) 
					{
						const FWidgetRow* Row = GetDataTableRowByTag<FWidgetRow>(WidgetMessageDataTable, Tag);
						NewMessageRow.Broadcast(*Row);
					}
				};

				
			}
		);
	}
}

