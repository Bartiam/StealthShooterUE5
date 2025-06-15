// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSCharacter_Base.h"
#include "SS_ImmortalEnemy_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API ASS_ImmortalEnemy_Base : public ASSCharacter_Base
{
	GENERATED_BODY()

public: // Functions

	ASS_ImmortalEnemy_Base();

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UNavigationInvokerComponent> NavigationInvoker;
	
};
