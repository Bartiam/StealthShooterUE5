// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SS_CardReaderWidget_Base.h"
#include "SS_KeypadWidget_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API USS_KeypadWidget_Base : public USS_CardReaderWidget_Base
{
	GENERATED_BODY()

protected: // Variables

	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<class USizeBox> SizeBoxToTextBlock;

	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<class USizeBox> SizeBoxToEnterTextBox;

	UPROPERTY(BlueprintReadWrite, Transient, meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> EnterTextBox;

	UPROPERTY(Transient, meta = (BindWidget))
	TObjectPtr<class UVerticalBox> ButtonVerticalBox;

public: // Functions

	UFUNCTION(BlueprintCallable)
	void CallOnCodeEntred(FName EntredCode, AActor* Interactor);

	virtual void CodeEntryActivated() override;

	virtual void CodeEntryDeactivated() override;
};
