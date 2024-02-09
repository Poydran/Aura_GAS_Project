// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability/AuraAttributeSet.h"
#include "AbilitySystemComponent.h"
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

void UOverlayWidgetController::BindCallbacksToDataSources()
{
	if (const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet))
	{
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::OnHealthUpdate);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::OnMaxHealthUpdate);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::OnManaUpdate);
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::OnMaxManaUpdate);
	}
}

void UOverlayWidgetController::OnHealthUpdate(const FOnAttributeChangeData& UpdateData)
{
	OnHealthChanged.Broadcast(UpdateData.NewValue);
}

void UOverlayWidgetController::OnMaxHealthUpdate(const FOnAttributeChangeData& UpdateData)
{
	OnMaxHealthChanged.Broadcast(UpdateData.NewValue);
}

void UOverlayWidgetController::OnManaUpdate(const FOnAttributeChangeData& UpdateData)
{
	OnManaChanged.Broadcast(UpdateData.NewValue);
}

void UOverlayWidgetController::OnMaxManaUpdate(const FOnAttributeChangeData& UpdateData)
{
	OnMaxManaChanged.Broadcast(UpdateData.NewValue);
}
