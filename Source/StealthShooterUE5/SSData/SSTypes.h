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
enum class ESSPhysKeyType : uint8
{
	None UMETA(DisplayName = "None"),
	Door_Key UMETA(DisplayName = "Door Key"),
	Locker_Key UMETA(DisplayName = "Locker Key"),
};

UENUM(BlueprintType)
enum class ESSCardType : uint8
{
	None UMETA(DisplayName = "None"),
	Security_Card UMETA(DisplayName = "Security Card"),
	Laboratory_Surveillance_Card UMETA(DisplayName = "Laboratory Surveillance Card"),
	Master_Card UMETA(DisplayName = "Master Card"),
};

UENUM(BlueprintType)
enum class ESSItemAccessType : uint8
{
	None UMETA(DisplayName = "None"),
	Physical_Key UMETA(DisplayName = "Physical Key"),
	Card_Key UMETA(DisplayName = "Card Key"),
};

USTRUCT(BlueprintType)
struct FKeyPermission
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESSItemAccessType ItemAccessType = ESSItemAccessType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESSCardType CardType = ESSCardType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESSPhysKeyType PhysKeyType = ESSPhysKeyType::None;
};

USTRUCT(BlueprintType)
struct FLineSize
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Start = FVector2D();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D End = FVector2D();
};

USTRUCT(BlueprintType)
struct FPickUpItemInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name_ID = FName();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemName = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ItemDescription = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FKeyPermission KeyPepmission = FKeyPermission();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ASS_PickUpItem_Base> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> ItemIcon_Rotated;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FIntPoint IconSize = FIntPoint(1, 1);

	// If the truth cannot be thrown out and haven't physics
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsImportantItem = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsRotated = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UGameplayEffect> GameplayEffect_Class;
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
