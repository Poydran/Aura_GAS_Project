// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "Ability/AuraAttributeSet.h"
#include "GameplayTags.h"
#include "Interfaces/CombatInterface.h"
#include "Ability/Data/ClassInfoAsset.h"
#include "AuraAbilityTypes.h"
#include "Ability/AuraAbilitySystemFunctionLibrary.h"
#include "GameplayEffectAttributeCaptureDefinition.h"
#include "Ability/MMC/AuraDamageExecutionCalculation.h"


struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armorpierce);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritResi);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritRate);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MysticResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDef;


	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armorpierce, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CritResi, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CritRate, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CritDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, MysticResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, PhysicalResistance, Target, false);
	}

	void SetCaptureMap()
	{
		TagsToCaptureDef.Add(FAuraGameplayTags::Get().Attributes_Secondary_Armor, ArmorDef);
		TagsToCaptureDef.Add(FAuraGameplayTags::Get().Attributes_Secondary_BlockChance, BlockChanceDef);
		TagsToCaptureDef.Add(FAuraGameplayTags::Get().Attributes_Secondary_ArmorPierce,ArmorpierceDef);
		TagsToCaptureDef.Add(FAuraGameplayTags::Get().Attributes_Secondary_CritResi, CritResiDef);
		TagsToCaptureDef.Add(FAuraGameplayTags::Get().Attributes_Secondary_CritRate, CritRateDef);
		TagsToCaptureDef.Add(FAuraGameplayTags::Get().Attributes_Secondary_CritDamage, CritDamageDef);
		TagsToCaptureDef.Add(FAuraGameplayTags::Get().Attributes_FireResistance,FireResistanceDef);
		TagsToCaptureDef.Add(FAuraGameplayTags::Get().Attributes_LightningResistance, LightningResistanceDef);
		TagsToCaptureDef.Add(FAuraGameplayTags::Get().Attributes_MysticResistance, MysticResistanceDef);
		TagsToCaptureDef.Add(FAuraGameplayTags::Get().Attributes_PhysicalResistance, PhysicalResistanceDef);
	}


};

static const AuraDamageStatics& DamageStatics()
{


	static AuraDamageStatics Dstatics;
	Dstatics.SetCaptureMap();

	return Dstatics;
}


UAuraDamageExecutionCalculation::UAuraDamageExecutionCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorpierceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritRateDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritResiDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().MysticResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);

	

}


void UAuraDamageExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	
	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParams.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	ICombatInterface* TargetInterface = Cast<ICombatInterface>(TargetAvatar);
	ICombatInterface* SourceInterface = Cast<ICombatInterface>(SourceAvatar);

	UClassInfoAsset* ClassInfo = UAuraAbilitySystemFunctionLibrary::GetClassInfoAsset(SourceAvatar);
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

//Get Damage Set By Caller Magnitude
	float Damage = 0.f;
	for (const auto& Tag : FAuraGameplayTags::Get().DamageTypesToResistances)
	{
		
		const FGameplayTag DamageTypeTag = Tag.Key;
		const FGameplayTag ResistanceTag = Tag.Value;

		checkf(DamageStatics().TagsToCaptureDef.Contains(ResistanceTag), TEXT("Tag Not defined: %s"), *ResistanceTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = DamageStatics().TagsToCaptureDef[ResistanceTag];
		
		float DamageValue = Spec.GetSetByCallerMagnitude(Tag.Key);

		//Capture Resistances for Type Specific Damage Calcs
		float ResistanceValue = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluateParams, ResistanceValue);
		ResistanceValue = FMath::Clamp(ResistanceValue, 0.f, 100.f);

		DamageValue *= (100.f - ResistanceValue) / 100.f;


		Damage += DamageValue;
	}
	

//Capture Blockchance on Target and determin if Hit was Blocked.
	
	const float BlockCalc = FMath::RandRange(1.f, 100.f);
	float BlockChanceValue = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluateParams, BlockChanceValue);
//If Block, halve Incoming Damage
	if (bool bBlocked = BlockChanceValue >= BlockCalc) 
	{
		Damage *= 0.5;
		UAuraAbilitySystemFunctionLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);
	}



	

//Capture ArmorPierce and determin Ignore of Armor
	float ArmorpierceValue = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorpierceDef, EvaluateParams, ArmorpierceValue);

//Capture Armor and determin Defensive Values
	float TargetArmorValue = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluateParams, TargetArmorValue);

//Capture CritResi
	float CritResistanceValue = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritResiDef, EvaluateParams, CritResistanceValue);

//Capture CritDamage
	float CritDamageValue = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritDamageDef, EvaluateParams, CritDamageValue);

//Capture CritRate
	float CritRateValue = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritRateDef, EvaluateParams, CritRateValue);

//Get Damage Calc Coefficients
	//EffectiveArmor Coefficient
	FRealCurve* EffectivaArmorCurve = ClassInfo->DamageCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const float ArmorCoefficient = EffectivaArmorCurve->Eval(TargetInterface->GetCombatantLevel());
	//Armorpierce Coefficient
	FRealCurve* ArmorpierceCurve = ClassInfo->DamageCoefficients->FindCurve(FName("Armorpierce"), FString());
	const float ArmorpierceCoefficient = ArmorpierceCurve->Eval(SourceInterface->GetCombatantLevel());
	//CritResi Coefficient
	FRealCurve* CritResiCurve = ClassInfo->DamageCoefficients->FindCurve(FName("CritResi"), FString());
	const float CritResiCoefficient = CritResiCurve->Eval(TargetInterface->GetCombatantLevel());

//Determin if CriticalHit
float CritChanceThreshold = FMath::RandRange(1, 100);

//If CriticalHit multiply Damage time CritDamage
if (bool bCrit = CritRateValue > (CritChanceThreshold + (CritResistanceValue * 0.75)))
{
	Damage += CritDamageValue;
	UAuraAbilitySystemFunctionLibrary::SetIsCriticalHit(EffectContextHandle, bCrit);
}

//True Damage Calculation 
	const float EffectiveArmor = TargetArmorValue *= (100 - ArmorpierceValue * ArmorpierceCoefficient) / 100.f;
	Damage *= (100 - EffectiveArmor * ArmorCoefficient) / 100.f;

//Output of Calculation to Attribute
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive,Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
