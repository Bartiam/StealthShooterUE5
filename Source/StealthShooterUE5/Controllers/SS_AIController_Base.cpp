// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_AIController_Base.h"
#include "BehaviorTree/BehaviorTree.h"
#include "../Characters/SSCharacter_Base.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"



ASS_AIController_Base::ASS_AIController_Base()
{
	// Create AI perception component
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AI Perception"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight Config"));

	// Set configure senses
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->StaticClass());

	SightConfig->SetPeripheralVisionAngle()
}



void ASS_AIController_Base::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);

	if (auto CurrentNPC = Cast<ASSCharacter_Base>(GetPawn()))
	{
		CurrentNPC->GetMesh();

		
	}
}
