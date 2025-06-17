// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_ImmortalEnemy_Base.h"
#include "Components/CapsuleComponent.h"
#include "../Controllers/SS_AIController_Base.h"
#include "NavigationInvokerComponent.h"

#include "../Controllers/AISenses/SS_SenseConfigSight.h"



ASS_ImmortalEnemy_Base::ASS_ImmortalEnemy_Base()
{
	// Set base specifications
	GetMesh()->SetWorldScale3D(FVector(1.1f, 1.1f, 1.1f));
	GetMesh()->SetWorldLocation(FVector(0.f, 0.f, -108.f));

	GetCapsuleComponent()->SetCapsuleHalfHeight(105.f);

	// Create Navigation Invoker and set base specifications
	NavigationInvoker = CreateDefaultSubobject<UNavigationInvokerComponent>(FName("Navigation Invoker"));
}

UNavigationInvokerComponent* ASS_ImmortalEnemy_Base::GetNavigationInvoker()
{
	return NavigationInvoker;
}



void ASS_ImmortalEnemy_Base::BeginPlay()
{
	Super::BeginPlay();
}



void ASS_ImmortalEnemy_Base::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	OutLocation = GetMesh()->GetSocketLocation(FName("HeadSocket"));
	OutRotation = GetMesh()->GetSocketRotation(FName("HeadSocket"));
}
