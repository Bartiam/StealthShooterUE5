// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SSTypes.generated.h"

UENUM(BlueprintType)
enum class ESSInputID : uint8
{
	Walk_Input UMETA(DisplayName = "Walk Input"),
	Run_Input UMETA(DisplayName = "Run Input"),
	Crouch_Input UMETA(DisplayName = "Crouch Input"),
	Crouch_Walk_Input UMETA(DisplayName = "Crouch Walk Input"),
	Reload_Input UMETA(DisplayName = "Reload Input"),
	Dodge_Input UMETA(DisplayName = "Dodge Input"),
};

UCLASS()
class STEALTHSHOOTERUE5_API USSTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
