// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_AIController_Base.h"
#include "../Characters/SSCharacter_Base.h"

#include "BehaviorTree/BehaviorTree.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"



ASS_AIController_Base::ASS_AIController_Base()
{
	// Create AI perception component
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AI Perception"));
	
	// Create AI sense sight
	AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sense Config Sight"));

	// Added senses
	PerceptionComponent->ConfigureSense(*AISenseConfigSight);
}



ETeamAttitude::Type ASS_AIController_Base::GetTeamAttitudeTowards(const AActor& OtherActor) const
{
	// Checking that's pawn
	if (auto IsThisPawn = Cast<APawn>(&OtherActor) == nullptr)
		return ETeamAttitude::Neutral;
	// Trying cast to Generic Cnterface
	auto VisibleTarget = Cast<IGenericTeamAgentInterface>(&OtherActor);
	// Checking that's nit nullptr
	if (!VisibleTarget)
		return ETeamAttitude::Neutral;
	// Checking is this enemy ?
	if (VisibleTarget->GetGenericTeamId() != CurrentNPC->GetGenericTeamId() &&
		VisibleTarget->GetGenericTeamId() != FGenericTeamId(static_cast<uint8>(ESSTeamID::Zombie_Team)))
	{
		return ETeamAttitude::Hostile;
	}

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

	if (NewPawn->Implements<UCharacterInterface>())
	{
		CurrentNPC = ICharacterInterface::Execute_GetOwnerCharacter(NewPawn);
	}
}
