// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/OverlayWidgetController.h"
#include "UI/AttributeWidgetController.h"
#include "UI/WidgetMaster.h"
#include "Player/AuraHUD.h"

// wird in InitOverlay ausgeführt um den OverlayWidgetController zu erstellen und alles seine DataSourcen zu etablieren
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

UAttributeWidgetController* AAuraHUD::GetAttributeWidgetController(const FDataSources& DataSources)
{
	if (!AttributeWidgetController)
	{
		AttributeWidgetController = NewObject<UAttributeWidgetController>(this, AttributeWidgetControllerClass);
		AttributeWidgetController->SetDataSources(DataSources);
		AttributeWidgetController->BindCallbacksToDataSources();
	}

	return AttributeWidgetController;
}


//Initialisiert den OverlayWidgetContoller für den Player 
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

void AAuraHUD::CloseAttributeOverlay()
{
	if (!AttributeOverlayWidget) return;

	AttributeOverlayWidget->RemoveFromParent();
	AttributeOverlayWidget = nullptr;


}

void AAuraHUD::OpenAttributeOverlay(const FVector2D& ViewportSize)
{
	checkf(AttributeOverlayClass,TEXT("Attribute Overlay Not Set."));

	AttributeOverlayWidget = CreateWidget<UWidgetMaster>(GetOwningPlayerController(), AttributeOverlayClass, FName("AttributeOverlay"));


	FVector2D ViewportPosition = ViewportSize * FVector2D(0.f, .95f);
	AttributeOverlayWidget->SetPositionInViewport(ViewportPosition);
	AttributeOverlayWidget->SetAlignmentInViewport(FVector2D(0.f, 1.f));
	AttributeOverlayWidget->AddToViewport();
}

void AAuraHUD::InteractWithAttributeOverlay(const FVector2D& ViewportSize)
{
	if (AttributeOverlayWidget)
	{
		CloseAttributeOverlay();
	}
	else
	{
		OpenAttributeOverlay(ViewportSize);
	}
}




	
