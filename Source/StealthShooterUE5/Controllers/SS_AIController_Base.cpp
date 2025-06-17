// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_AIController_Base.h"
#include "../Characters/SSCharacter_Base.h"

#include "BehaviorTree/BehaviorTree.h"

#include "Perception/AIPerceptionComponent.h"
#include "AISenses/SS_SenseConfigSight.h"
#include "Perception/AISenseConfig_Hearing.h"



ASS_AIController_Base::ASS_AIController_Base()
{
	// Create AI perception component
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AI Perception"));
	
	// Create AI sense sight
	AISenseConfigSight = CreateDefaultSubobject<USS_SenseConfigSight>(FName("Sense Config Sight"));

	// Added senses
	PerceptionComponent->ConfigureSense(*AISenseConfigSight);
}



FGenericTeamId ASS_AIController_Base::GetGenericTeamId() const
{ return TeamId; }



ETeamAttitude::Type ASS_AIController_Base::GetTeamAttitudeTowards(const AActor & OtherActor) const
{
	return ETeamAttitude::Type();
}



void ASS_AIController_Base::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);
}



void ASS_AIController_Base::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	if (auto Agent = Cast<ASSCharacter_Base>(NewPawn))
	{
		CurrentNPC = Agent;
		TeamId = FGenericTeamId(CurrentNPC->ID);
	}
}
