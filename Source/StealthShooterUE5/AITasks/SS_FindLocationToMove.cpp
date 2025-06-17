// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_FindLocationToMove.h"
#include "../Controllers/SS_AIController_Base.h"
#include "../Characters/SS_ImmortalEnemy_Base.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"



USS_FindLocationToMove::USS_FindLocationToMove(FObjectInitializer const& ObjectInitializer)
{
	NodeName = FString("Find Location To Move In Nav Mesh");
}



EBTNodeResult::Type USS_FindLocationToMove::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	// Get owner controller from behavior tree
	if (auto const CurrentAIController = Cast<ASS_AIController_Base>(OwnerComponent.GetOwner()))
	{
		if (auto OwnerNPC = Cast<ASS_ImmortalEnemy_Base>(CurrentAIController->GetPawn()))
		{
			// Get NPC Location
			auto CharacterLocation = OwnerNPC->GetActorLocation();

			// Get the navigation system and generate random location
			if (auto const NavSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation ReceivedLocation;
				if (NavSystem->GetRandomPointInNavigableRadius(CharacterLocation, SearchRadius, ReceivedLocation))
				{
					OwnerComponent.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ReceivedLocation);
				}

				// Finished with success 
				FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}

	}

	return EBTNodeResult::Failed;
}
