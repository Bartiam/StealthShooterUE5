// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SS_Item_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API USS_Item_Base : public UObject
{
	GENERATED_BODY()
	
public: // Variables

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Specifications")
	int64 ItemID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Specifications")
	FText ItemName = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Specifications")
	FText ItemDescription = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Specifications")
	TObjectPtr<UTexture2D> ItemIcon;


};
