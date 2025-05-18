// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_BigPhysObject_Base.h"

ASS_BigPhysObject_Base::ASS_BigPhysObject_Base()
{
	ObjectCircled->SetSimulatePhysics(true);
	ObjectCircled->SetCollisionProfileName("PhysicsBody");
}
