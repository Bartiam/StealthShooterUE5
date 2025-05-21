// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "SSTypes.generated.h"

UENUM(BlueprintType)
enum class ESSInputID : uint8
{
	Walk_Input UMETA(DisplayName = "Walk Input"),
	Crouch_Input UMETA(DisplayName = "Crouch Input"),
	Reload_Input UMETA(DisplayName = "Reload Input"),
	Dodge_Input UMETA(DisplayName = "Dodge Input"),
	Interact_Input UMETA(DisplayName = "Interact Input"),
	Inventory_Input UMETA(DisplayName = "Inventory Input"),
};

UENUM(BlueprintType)
enum class ESSRoomTypes : uint8
{
	Begin_Play_Room UMETA(DisplayName = "Begin Play Room"),
	Laboratory_Room UMETA(DisplayName = "Laboratory Room"),
	Security_Room UMETA(DisplayName = "Security Room"),
	Distribution_Room UMETA(DisplayName = "Distribution Room"),
	Experimental_Room UMETA(DisplayName = "Experimental Room"),
	Arena_Room UMETA(DisplayName = "Arena Room"),
	Surveillance_Room UMETA(DisplayName = "Surveillance Room"),
	Hallway_Room UMETA(DisplayName = "Hallway Room")
};

UENUM(BlueprintType)
enum class ESSCardTypes : uint8
{
	None_Card UMETA(DisplayName = "None Card"),
	Red_Security_Card UMETA(DisplayName = "Red Security Card"),
	Blue_Surveillance_Card UMETA(DisplayName = "Blue Surveillance Card"),
	White_Master_Card UMETA(DisplayName = "White Master Card")
};

USTRUCT(BlueprintType)
struct FPickUpItemInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name_ID = FName();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemDescription = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ASS_PickUpItem_Base> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> ITemIcon;

	// If the truth cannot be thrown out and haven't physics
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsImportantItem = false;
};

USTRUCT(BlueprintType)
struct FCharacterMovementSpeed
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float WalkSpeed = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag WalkTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CrouchSpeed = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag CrouchTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RunSpeed = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CrouchedWalkSpeed = 0.f;

	// Buff/dubaff
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ImproveSpeedFromStimulator = 0.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag SpeedStimulatoTag;
};

UCLASS()
class STEALTHSHOOTERUE5_API USSTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
