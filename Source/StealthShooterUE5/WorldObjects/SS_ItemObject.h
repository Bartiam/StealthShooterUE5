// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "../SSData/SSTypes.h"

#include "SS_ItemObject.generated.h"



UCLASS(Blueprintable)
class STEALTHSHOOTERUE5_API USS_ItemObject : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	FPickUpItemInfo ItemInfo = FPickUpItemInfo();

	UFUNCTION(BlueprintCallable)
	void RotateImage();

	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffectFromThisItem(AActor* Interactor);
};
