// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/OverlayWidgetController.h"
#include "UI/WidgetMaster.h"
#include "Player/AuraHUD.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FDataSources& DataSources)
{

	if (!OverlayWidgetController) 
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetDataSources(DataSources);
		OverlayWidgetController->BindCallbacksToDataSources();
	}

	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass Not Set"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass Not Set"));
	OverlayWidget = CreateWidget<UWidgetMaster>(GetOwningPlayerController(), OverlayWidgetClass, FName("Overlay"));

	const FDataSources DataSources = FDataSources(PC, PS, ASC, AS);
	UOverlayWidgetController* OverlayController = GetOverlayWidgetController(DataSources);

	OverlayWidget->SetWidgetController(OverlayController);
	OverlayController->BroadcastInitialWidgetValues();
	


	OverlayWidget->AddToViewport();



}




	
