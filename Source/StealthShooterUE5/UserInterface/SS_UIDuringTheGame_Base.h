// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "../Interfaces/CharacterInterface.h"

#include "SS_UIDuringTheGame_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API USS_UIDuringTheGame_Base : public UUserWidget
{
	GENERATED_BODY()

protected: // Variables

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class ASSCharacter_Base> OwningCharacter;

protected: // Functions

	virtual void NativeConstruct() override;
	
};
