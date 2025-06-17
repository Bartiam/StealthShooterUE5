// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SS_AIController_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_AIController_Base : public AAIController
{
	GENERATED_BODY()

public: // Functions
	
	ASS_AIController_Base();

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Specifications")
	TObjectPtr<class UBehaviorTree> BehaviorTree;

	TObjectPtr<class USS_SenseConfigSight> AISenseConfigSight;

protected: // Functions

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* NewPawn) override;
};
