// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "CharacterAbilities.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UCharacterAbilities : public UInterface
{
	GENERATED_BODY()
};



class STEALTHSHOOTERUE5_API ICharacterAbilities
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	class ASSCharacter_Base* GetCharacter();
};
