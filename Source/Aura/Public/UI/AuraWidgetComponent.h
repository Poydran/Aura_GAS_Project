// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "AuraWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Widget|Text")
	void PlayDamageText(float Damage,bool bBlockedHit, bool bCriticalHit);
	
};
