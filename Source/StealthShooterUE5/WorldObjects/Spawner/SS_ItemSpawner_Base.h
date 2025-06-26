// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../SSData/SSTypes.h"

#include "SS_ItemSpawner_Base.generated.h"

UCLASS()
class STEALTHSHOOTERUE5_API ASS_ItemSpawner_Base : public AActor
{
	GENERATED_BODY()
	
public:	

	ASS_ItemSpawner_Base();

protected: // Variables

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<class ASS_SpawnMarker_Base>> SpawnMarkers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESSRoomType RoomType;

protected:

	virtual void BeginPlay() override;

private: // Functions 

	void SpawnItemsSecurityRoom();

	void SpawnObjectInTheRoom();

	bool CheckingSpawnedObjectInTheRoom();

};
