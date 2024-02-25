// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController.h"
#include "Player/AuraHUD.h"
#include "Player/AuraState.h"
#include "Ability/AuraAttributeSet.h"
#include "UI/AttributeWidgetController.h"
#include "AbilitySystemComponent.h"
#include "Ability/AuraAbilitySystemFunctionLibrary.h"

UOverlayWidgetController* UAuraAbilitySystemFunctionLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{

	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0);

	if (AAuraHUD* AuraHUD = PC->GetHUD<AAuraHUD>())
	{
		AAuraState* PS = PC->GetPlayerState<AAuraState>();
		UAttributeSet* AS = PS->GetAttributeSet();
		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		const FDataSources DataSource = FDataSources(PC,PS,ASC,AS);
		if (UOverlayWidgetController* OverlayController = AuraHUD->GetOverlayWidgetController(DataSource)) return OverlayController;
		
	}
	return nullptr;
}

UAttributeWidgetController* UAuraAbilitySystemFunctionLibrary::GetAttributeWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);

	if (AAuraHUD* AuraHUD = PC->GetHUD<AAuraHUD>())
	{
		AAuraState* PS = PC->GetPlayerState<AAuraState>();
		UAttributeSet* AS = PS->GetAttributeSet();
		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		const FDataSources DataSource = FDataSources(PC, PS, ASC, AS);
		if (UAttributeWidgetController* AttributeController = AuraHUD->GetAttributeWidgetController(DataSource)) return AttributeController;
	}
	return nullptr;
}
