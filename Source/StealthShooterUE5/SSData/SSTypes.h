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

UENUM(BlueprintType)
enum class ESSRoomTypes : uint8
{
	Begin_Play_Room UMETA(DisplayName = "Begin Play Room"),
	End_Play_Room UMETA(DisplayName = "End Play Room"),
	Laboratory_Room UMETA(DisplayName = "Laboratory Room"),
	Security_Room UMETA(DisplayName = "Security Room"),
	Distribution_Room UMETA(DisplayName = "Distribution Room"),
	Experimental_Room UMETA(DisplayName = "Experimental Room"),
	Arena_Room UMETA(DisplayName = "Arena Room"),
	Surveillance_Room UMETA(DisplayName = "Surveillance Room"),
	Hallway_Room UMETA(DisplayName = "Hallway Room")
};

UCLASS()
class STEALTHSHOOTERUE5_API USSTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
