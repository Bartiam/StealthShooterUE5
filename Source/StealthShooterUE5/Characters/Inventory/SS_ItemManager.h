// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SS_ItemManager.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API USS_ItemManager : public UObject
{
	GENERATED_BODY()
	
public:



private: // Variables

	TObjectPtr<UDataTable> DT_ItemInfo;
};
