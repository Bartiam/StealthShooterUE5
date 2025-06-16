// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_SensoryOrgans_Base.h"
#include "Perception/AIPerceptionComponent.h"



// Sets default values
ASS_SensoryOrgans_Base::ASS_SensoryOrgans_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add tag, for checking child actors in the NPC
	Tags.Add(FName("Sensory Organs"));
}



void ASS_SensoryOrgans_Base::SetPerceptionComponent(UAIPerceptionComponent* NewPerceptionComponent)
{
	PerceptionComponent = NewPerceptionComponent;
}



UAIPerceptionComponent* ASS_SensoryOrgans_Base::GetPerceptionComponent() const
{ return PerceptionComponent; }


