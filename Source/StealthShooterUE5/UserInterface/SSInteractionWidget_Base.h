// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SSInteractionWidget_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API USSInteractionWidget_Base : public UUserWidget
{
	GENERATED_BODY()
	
public: // Variables

	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<class UImage> Image;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<class UWidgetAnimation> AppearMarkObject;
};
