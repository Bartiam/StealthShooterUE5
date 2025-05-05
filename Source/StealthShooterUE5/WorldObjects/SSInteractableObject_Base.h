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

private: // Variables

	TSubclassOf<class USSInteractionWidget_Base> InteractionWidget_Class;

protected: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UBoxComponent> OverlapBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UStaticMeshComponent> ObjectCircled;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UWidgetComponent> InteractionWidget;

protected: // Functions

	virtual void BeginPlay() override;

	virtual void CanReceiveTrace_Implementation(bool bIsCanInteract) override;
};
