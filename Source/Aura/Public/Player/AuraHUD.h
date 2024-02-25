// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

/**
 * 
 */


struct FDataSources;
class UOverlayWidgetController;
class UAttributeWidgetController;
class UWidgetMaster;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	//Gibt den Controller des Overlay Widget zurück und erstellt ihn falls er noch nicht existiert
	

	UOverlayWidgetController* GetOverlayWidgetController(const FDataSources& DataSources);

	UAttributeWidgetController* GetAttributeWidgetController(const FDataSources& DataSources);

	//Erstellt das Overlay anhand seiner Klasse,
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	void InteractWithAttributeOverlay(const FVector2D& ViewportSize);

protected:



private:

	//OverlayWidget /start
	UPROPERTY(EditDefaultsOnly, Category = "WidgetController|Overlay")
	TSubclassOf< UWidgetMaster> OverlayWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetController|AttributeOverlay")
	TSubclassOf< UWidgetMaster> AttributeOverlayClass;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetController|Overlay")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetController|AttributeOverlay")
	TSubclassOf<UAttributeWidgetController> AttributeWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UWidgetMaster> OverlayWidget;

	UPROPERTY()
	TObjectPtr<UWidgetMaster> AttributeOverlayWidget;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY()
	TObjectPtr<UAttributeWidgetController> AttributeWidgetController;
	//OverlayWidget /end
	
	void CloseAttributeOverlay();

	void OpenAttributeOverlay(const FVector2D& ViewportSize);
};
