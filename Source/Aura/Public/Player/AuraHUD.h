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

	//Erstellt das Overlay anhand seiner Klasse,
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:



private:

	//OverlayWidget /start
	UPROPERTY(EditDefaultsOnly, Category = Overlay)
	TSubclassOf< UWidgetMaster> OverlayWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = Overlay)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UWidgetMaster> OverlayWidget;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	//OverlayWidget /end
};
