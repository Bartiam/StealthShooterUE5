// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_ImmortalEnemy_Base.h"
#include "Components/CapsuleComponent.h"



ASS_ImmortalEnemy_Base::ASS_ImmortalEnemy_Base()
{
	// Set base specifications
	GetMesh()->SetWorldScale3D(FVector(1.1f, 1.1f, 1.1f));
	GetMesh()->SetWorldLocation(FVector(0.f, 0.f, -100.f));

	GetCapsuleComponent()->SetCapsuleHalfHeight(100.f);
}
