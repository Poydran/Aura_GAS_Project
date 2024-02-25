// Fill out your copyright notice in the Description page of Project Settings.

#include "Interfaces/CombatInterface.h"
#include "Ability/AuraAttributeSet.h"
#include "Ability/MMC/MMC_MaxMana.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{

	float Intelligence;
	FAggregatorEvaluateParameters EvaluatedParams;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluatedParams, Intelligence);
	ICombatInterface* Interface = CastChecked<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const float PlayerLevel = Interface->GetCombatantLevel();
	Intelligence = FMath::Max<float>(Intelligence, 0.f);

	return 50 + 2 * Intelligence + 15 * PlayerLevel;
}
