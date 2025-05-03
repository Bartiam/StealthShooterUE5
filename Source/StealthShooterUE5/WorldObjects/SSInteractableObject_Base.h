// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../Interfaces/Interactable.h"

#include "SSInteractableObject_Base.generated.h"

UCLASS()
class STEALTHSHOOTERUE5_API ASSInteractableObject_Base : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	// Functions
	
	ASSInteractableObject_Base();

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UWidgetComponent> PressWidget;

protected: // Functions
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
