// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "SS_FindLocationToMove.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API USS_FindLocationToMove : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public: // Functions

	explicit USS_FindLocationToMove(FObjectInitializer const& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory) override;

protected: // Variables

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI Specifications")
	float SearchRadius = 0.f;

};
