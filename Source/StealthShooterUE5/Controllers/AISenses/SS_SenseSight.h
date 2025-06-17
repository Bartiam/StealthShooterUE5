// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AISense_Sight.h"
#include "SS_SenseSight.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API USS_SenseSight : public UAISense_Sight
{
	GENERATED_BODY()
	
protected: // Functions

	virtual float Update() override;

public: // Functions

	USS_SenseSight();
	
};
