// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController.h"
#include "Player/AuraHUD.h"
#include "Player/AuraState.h"
#include "Ability/AuraAttributeSet.h"
#include "UI/AttributeWidgetController.h"
#include "GameMode/AuraGameMode.h"
#include "AuraAbilityTypes.h"
#include "AbilitySystemComponent.h"
#include "Ability/AuraAbilitySystemFunctionLibrary.h"

UOverlayWidgetController* UAuraAbilitySystemFunctionLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject,0);

	if (AAuraHUD* AuraHUD = PC->GetHUD<AAuraHUD>())
	{
		AAuraState* PS = PC->GetPlayerState<AAuraState>();
		UAttributeSet* AS = PS->GetAttributeSet();
		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		const FDataSources DataSource = FDataSources(PC,PS,ASC,AS);
		if (UOverlayWidgetController* OverlayController = AuraHUD->GetOverlayWidgetController(DataSource)) return OverlayController;
		
	}
	return nullptr;
}

UAttributeWidgetController* UAuraAbilitySystemFunctionLibrary::GetAttributeWidgetController(const UObject* WorldContextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);

	if (AAuraHUD* AuraHUD = PC->GetHUD<AAuraHUD>())
	{
		AAuraState* PS = PC->GetPlayerState<AAuraState>();
		UAttributeSet* AS = PS->GetAttributeSet();
		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		const FDataSources DataSource = FDataSources(PC, PS, ASC, AS);
		if (UAttributeWidgetController* AttributeController = AuraHUD->GetAttributeWidgetController(DataSource)) return AttributeController;
	}
	return nullptr;
}

void UAuraAbilitySystemFunctionLibrary::InitEnemyAttributes(const UObject* WorldContextObject, EClassTypes ClassType, float Level, UAbilitySystemComponent* ASCToApplyTo)
{
	
	UClassInfoAsset* EnemyClassInfo = GetClassInfoAsset(WorldContextObject);

	FCharacterClassesDefaultInfo DefaultInfo = EnemyClassInfo->GetCharacterInfo(ClassType);

	FGameplayEffectContextHandle PrimaryEffectContext = ASCToApplyTo->MakeEffectContext();
	PrimaryEffectContext.AddSourceObject(ASCToApplyTo->GetAvatarActor());

	const FGameplayEffectSpecHandle EffectSpecHandle = ASCToApplyTo->MakeOutgoingSpec(DefaultInfo.PrimaryAttributesGE , Level, PrimaryEffectContext);
	ASCToApplyTo->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryEffectContext = ASCToApplyTo->MakeEffectContext();
	SecondaryEffectContext.AddSourceObject(ASCToApplyTo->GetAvatarActor());

	const FGameplayEffectSpecHandle SecondaryEffectSpecHandle = ASCToApplyTo->MakeOutgoingSpec(EnemyClassInfo->SecondaryAttributesGE, Level, SecondaryEffectContext);
	ASCToApplyTo->ApplyGameplayEffectSpecToSelf(*SecondaryEffectSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalEffectContext = ASCToApplyTo->MakeEffectContext();
	VitalEffectContext.AddSourceObject(ASCToApplyTo->GetAvatarActor());
	const FGameplayEffectSpecHandle VitalEffectSpecHandle = ASCToApplyTo->MakeOutgoingSpec(EnemyClassInfo->VitalAttributesGE, Level, VitalEffectContext);
	ASCToApplyTo->ApplyGameplayEffectSpecToSelf(*VitalEffectSpecHandle.Data.Get());

}

void UAuraAbilitySystemFunctionLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASCToApplyTo)
{
	
	UClassInfoAsset* EnemyClassInfo = GetClassInfoAsset(WorldContextObject);

	for (auto& Ability : EnemyClassInfo->DefaultEnemyAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		ASCToApplyTo->GiveAbility(AbilitySpec);
	}
}

UClassInfoAsset* UAuraAbilitySystemFunctionLibrary::GetClassInfoAsset(const UObject* WorldContextObject)
{
	if (AAuraGameMode* AuraGM = Cast<AAuraGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		return AuraGM->ClassInfoAsset;
	}

	return nullptr;
}

bool UAuraAbilitySystemFunctionLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->IsBlockedHit();
	}

	return false;
}

bool UAuraAbilitySystemFunctionLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->IsCriticalHit();
	}

	return false;
}

void UAuraAbilitySystemFunctionLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bIsBlocked)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
	 AuraEffectContext->SetbIsBlockedHit(bIsBlocked);
	}
}

void UAuraAbilitySystemFunctionLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bIsCritical)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetbIsCriticalHit(bIsCritical);
	}
}
 