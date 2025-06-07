// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SS_PickUpItem_Base.h"
#include "../SSData/SSTypes.h"

#include "SS_Card_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_Card_Base : public ASS_PickUpItem_Base
{
	GENERATED_BODY()
	
protected: // Variables

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Card Specifications")
	TObjectPtr<class UTextRenderComponent> CardName_InTheWorld;

public: // Functions

	ASS_Card_Base();
};
