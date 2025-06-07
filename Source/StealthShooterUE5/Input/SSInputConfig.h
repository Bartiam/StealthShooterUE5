// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "../SSData/SSTypes.h"

#include "SSInputConfig.generated.h"

// Struct IA Binds
USTRUCT(BlueprintType)
struct FSSInputActionBinds
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> InputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	ESSInputID ButtonInputID;
};

UCLASS(BlueprintType, Blueprintable)
class STEALTHSHOOTERUE5_API USSInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TArray<FSSInputActionBinds> InputActionBinds;
};
