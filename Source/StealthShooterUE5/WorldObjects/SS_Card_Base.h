// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSInteractableObject_Base.h"

#include "../SSData/SSTypes.h"

#include "SS_Card_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_Card_Base : public ASSInteractableObject_Base
{
	GENERATED_BODY()
	
protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Specifications")
	ESSCardTypes ThisCardType;

public: // Functions

	ASS_Card_Base();
};
