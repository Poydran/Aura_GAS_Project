// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Input/InputDataAsset.h"
#include "AuraEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	

public:
	template <class UserClass, typename PressedFuncType, typename HeldFuncType, typename ReleasedFuncType >
	void BindAbilityActions(const UInputDataAsset* InputData, UserClass* Object, PressedFuncType PressedFunction, HeldFuncType HeldFunction, ReleasedFuncType ReleasedFunction);
};

template<class UserClass, typename PressedFuncType, typename HeldFuncType, typename ReleasedFuncType>
inline void UAuraEnhancedInputComponent::BindAbilityActions(const UInputDataAsset* InputData, UserClass* Object, PressedFuncType PressedFunction, HeldFuncType HeldFunction, ReleasedFuncType ReleasedFunction)
{
	check(InputData);

	for (const auto& Input : InputData->InputTagData) 
	{
		if (Input.InputAction && Input.AbilityTag.IsValid())
		{

			if (PressedFunction)
			{
				BindAction(Input.InputAction, ETriggerEvent::Started, Object, PressedFunction, Input.AbilityTag);
			}
			if (ReleasedFunction)
			{
				BindAction(Input.InputAction, ETriggerEvent::Completed, Object, ReleasedFunction, Input.AbilityTag);
			}
			if (HeldFunction) 
			{
				BindAction(Input.InputAction, ETriggerEvent::Triggered, Object, HeldFunction, Input.AbilityTag);
			}
		}
	}
}
