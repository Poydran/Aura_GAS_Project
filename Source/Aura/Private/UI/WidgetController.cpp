// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController.h"

void UWidgetController::SetDataSources(const FDataSources& DataSources)
{

	Playercontroller = DataSources.Playercontroller;
	PlayerState = DataSources.PlayerState;
	AbilitySystemComp = DataSources.AbilitySystemComponent;
	AttributeSet = DataSources.AttributeSet;

}

void UWidgetController::BroadcastInitialWidgetValues()
{
}

void UWidgetController::BindCallbacksToDataSources()
{
}
