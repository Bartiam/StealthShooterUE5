// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_AIController_Base.h"
#include "BehaviorTree/BehaviorTree.h"



void ASS_AIController_Base::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);
}
