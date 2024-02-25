// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Data/AttributeInfoAsset.h"

FAttributeInfo UAttributeInfoAsset::FindAttributeInfoforTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{

	for (const FAttributeInfo& Info : AttributeInfoArray)
	{
		if (Info.AttributeTag == AttributeTag)
		{
			return Info;
		}
	}
	if (bLogNotFound) 
	{
		UE_LOG(LogTemp, Error, TEXT("Cant find Info for Attribute [%s] on AttributeInfo[%s]"), *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FAttributeInfo();
}
