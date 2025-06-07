// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_ItemObject.h"
#include "../Characters/SSCharacter_Base.h"
#include "../GAS/SS_AbilitySystemComponent.h"



void USS_ItemObject::RotateImage()
{
	ItemInfo.bIsRotated = !ItemInfo.bIsRotated;

	ItemInfo.IconSize = FIntPoint(ItemInfo.IconSize.Y, ItemInfo.IconSize.X);
}



void USS_ItemObject::ApplyGameplayEffectFromThisItem(AActor* Interactor)
{
	// Check ASC and Effect != nullptr
	if (auto CharacterASC = ICharacterInterface::Execute_GetOwnerCharacter(Interactor)->GetAbilitySystemComponent())
	{
		// Create effect context for gameplay effect 
		FGameplayEffectContextHandle EffectContext = CharacterASC->MakeEffectContext();
		// The source of the effect created
		EffectContext.AddSourceObject(this);
		// Create a specification for the effect
		FGameplayEffectSpecHandle SpecHandle = CharacterASC->MakeOutgoingSpec(ItemInfo.GameplayEffect_Class, 1.f, EffectContext);
		// Check valid
		if (SpecHandle.IsValid())
		{
			// Apply gameplay effect to character
			CharacterASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}