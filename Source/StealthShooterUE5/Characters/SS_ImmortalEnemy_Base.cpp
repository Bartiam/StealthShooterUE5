// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_ImmortalEnemy_Base.h"
#include "Components/CapsuleComponent.h"
#include "../Controllers/SS_AIController_Base.h"
#include "../Controllers/AISenses/SS_SensoryOrgans_Base.h"
#include "NavigationInvokerComponent.h"



ASS_ImmortalEnemy_Base::ASS_ImmortalEnemy_Base()
{
	// Set base specifications
	GetMesh()->SetWorldScale3D(FVector(1.1f, 1.1f, 1.1f));
	GetMesh()->SetWorldLocation(FVector(0.f, 0.f, -108.f));

	GetCapsuleComponent()->SetCapsuleHalfHeight(105.f);

	// Create Navigation Invoker and set base specifications
	NavigationInvoker = CreateDefaultSubobject<UNavigationInvokerComponent>(FName("Navigation Invoker"));
}

ASS_SensoryOrgans_Base* ASS_ImmortalEnemy_Base::GetSensoryOrgans()
{ return SensoryOrgansComponent; }

void ASS_ImmortalEnemy_Base::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> ChildActors;
	GetAllChildActors(ChildActors);

	for (int i = 0; i < ChildActors.Num(); ++i)
		if (ChildActors[i]->ActorHasTag(FName("Sensory Organs")))
			SensoryOrgansComponent = Cast<ASS_SensoryOrgans_Base>(ChildActors[i]);
}
