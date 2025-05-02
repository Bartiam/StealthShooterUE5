// Fill out your copyright notice in the Description page of Project Settings.


#include "SSInteractAbility_Base.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"



void USSInteractAbility_Base::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FHitResult HitResult;

	if (auto PlayerCamera = ICharacterInterface::Execute_GetPlayerCameraComponent(GetAvatarActorFromActorInfo()))
	{
		FVector CameraLocation = PlayerCamera->GetComponentLocation();
		FVector EndLineTrace = CameraLocation + (PlayerCamera->GetForwardVector() * LineTraceLength);

		UKismetSystemLibrary::LineTraceSingle(GetWorld(), CameraLocation, EndLineTrace, ETraceTypeQuery::TraceTypeQuery1,
			false, IgnoreActors, EDrawDebugTrace::Persistent, HitResult, true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("This actor has't camera component!"), *GetName());
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}

	if (HitResult.GetActor() != nullptr && HitResult.GetActor()->Implements<UInteractable>())
		IInteractable::Execute_Interactable(HitResult.GetActor());

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
