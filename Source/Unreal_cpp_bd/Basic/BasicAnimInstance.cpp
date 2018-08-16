// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAnimInstance.h"
#include "Basic/BasicPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBasicAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	ABasicPlayer* Pawn = Cast<ABasicPlayer>(TryGetPawnOwner());

	if (Pawn && Pawn->IsValidLowLevel())
	{
		Speed = Pawn->GetCharacterMovement()->Velocity.Size();

		Direction = CalculateDirection(Pawn->GetCharacterMovement()->Velocity,
			Pawn->GetActorRotation());

		bIsCrouch = Pawn->bIsCrouched;
		bIsIronsight = Pawn->bIsIronSight;
	}
}
