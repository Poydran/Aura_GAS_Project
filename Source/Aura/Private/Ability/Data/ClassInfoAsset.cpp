// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/Data/ClassInfoAsset.h"

FCharacterClassesDefaultInfo UClassInfoAsset::GetCharacterInfo(EClassTypes ClassType) const
{

	return CharacterClassMap.FindChecked(ClassType);
}
