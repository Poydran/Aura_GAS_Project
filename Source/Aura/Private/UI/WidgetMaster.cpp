// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/WidgetController.h"
#include "UI/WidgetMaster.h"

void UWidgetMaster::SetWidgetController(UWidgetController* InWidgetController)
{
	WidgetController = InWidgetController;
	InitWidgetController();

}
