// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DataTypes.generated.h"

UENUM(BlueprintType)
enum class ESSAbilityInputID : uint8
{
	None, 
	Confirm,
	Cancel,
	Attack,
};

UCLASS()
class STEALTHSHOOTERUE5_API UDataTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
