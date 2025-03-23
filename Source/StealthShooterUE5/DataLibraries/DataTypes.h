// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "DataTypes.generated.h"

// Enumeration of the input ID
UENUM(BlueprintType)
enum class ESSAbilityInputID : uint8
{
	None UMETA(DisplayName = "None"),
	Confirm UMETA(DisplayName = "Confirm"),
	Cancel UMETA(DisplayName = "Cancel"),
	Attack UMETA(DisplayName = "Attack"),
	Test UMETA(DisplayName = "Test")
};

UCLASS()
class STEALTHSHOOTERUE5_API UDataTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
