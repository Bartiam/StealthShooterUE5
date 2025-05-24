// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "../SSData/SSTypes.h"

#include "SS_ItemObject.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API USS_ItemObject : public UObject
{
	GENERATED_BODY()

public:

	FPickUpItemInfo ItemInfo = FPickUpItemInfo();
};
