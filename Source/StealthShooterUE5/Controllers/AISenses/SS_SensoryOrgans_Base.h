// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SS_SensoryOrgans_Base.generated.h"

UCLASS()
class STEALTHSHOOTERUE5_API ASS_SensoryOrgans_Base : public AActor
{
	GENERATED_BODY()
	
public:	// Functions
	
	ASS_SensoryOrgans_Base();

	void SetPerceptionComponent(class UAIPerceptionComponent* NewPerceptionComponent);

	class UAIPerceptionComponent* GetPerceptionComponent() const;

private: // Variables

	TObjectPtr<class UAIPerceptionComponent> PerceptionComponent;
};
