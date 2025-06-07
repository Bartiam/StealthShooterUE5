// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "../SSData/SSTypes.h"

#include "SSRoomDataAsset_Base.generated.h"



UCLASS()
class STEALTHSHOOTERUE5_API USSRoomDataAsset_Base : public UDataAsset
{
	GENERATED_BODY()
	
public: // Variables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ESSRoomTypes RoomType = ESSRoomTypes::Begin_Play_Room;
};
