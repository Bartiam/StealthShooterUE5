// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SS_CardReaderWidget_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API USS_CardReaderWidget_Base : public UUserWidget
{
	GENERATED_BODY()
	
protected: // Variables

	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<class UBorder> BackgroundBorder;

	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText TextWhenDoorLocked = FText();

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<class UWidgetAnimation> AppearReaderMessage;

private: // Variables

	FLinearColor OpenDoorColor = FLinearColor(0.f, 1.f, 0.f ,0.25f);

	FLinearColor LockDoorColor = FLinearColor(1.f, 0.f, 0.f, 0.25f);

	FText ErrorMessage = INVTEXT("ERROR!");

public: // Variables

	TObjectPtr<class ASS_DisplayReader_Base> OwnerCodeReader;

public: // Functions

	UFUNCTION()
	virtual void BindOnCodeEntred(FPickUpItemInfo ItemInfo, AActor* Interactor);

	UFUNCTION()
	void SetBrushColorToOpenDoor(const bool& bIsDoorLock);

	virtual void CodeEntryActivated();

	virtual void CodeEntryDeactivated();

	void ShowMessageEntry();
};
