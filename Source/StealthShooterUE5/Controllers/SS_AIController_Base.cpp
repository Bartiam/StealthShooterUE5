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



ETeamAttitude::Type ASS_AIController_Base::GetTeamAttitudeTowards(const AActor& OtherActor) const
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString("AI Controller!"));

	// Checking that's pawn
	if (auto IsThisPawn = Cast<APawn>(&OtherActor) == nullptr)
		return ETeamAttitude::Neutral;

	auto VisibleTarget = Cast<IGenericTeamAgentInterface>(&OtherActor);

	if (!VisibleTarget)
		return ETeamAttitude::Neutral;

	if (VisibleTarget->GetGenericTeamId() != CurrentNPC->GetGenericTeamId() &&
		VisibleTarget->GetGenericTeamId() != FGenericTeamId(static_cast<uint8>(ESSTeamID::Zombie_Team)))
	{
		return ETeamAttitude::Hostile;
	}

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString("Enemy" + VisibleTarget->GetGenericTeamId()));
	return ETeamAttitude::Neutral;
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
	}
}
