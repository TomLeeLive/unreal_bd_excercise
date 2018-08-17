// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicPCM.h"
#include "Basic/BasicPlayer.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABasicPCM::ABasicPCM()
{
}

void ABasicPCM::BeginPlay()
{
	Super::BeginPlay();
	ABasicPlayer* Pawn = PCOwner ? Cast<ABasicPlayer>(PCOwner->GetPawn()) : nullptr;

	if (Pawn)
	{
		SpringArmOffset = Pawn->SpringArm->GetRelativeTransform().GetLocation();
		DefaultFOV = Pawn->bIsIronSight ? IronSightFOV : NormalFOV;
	}
}

void ABasicPCM::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);

	ABasicPlayer* Pawn = PCOwner ? Cast<ABasicPlayer>(PCOwner->GetPawn()) : nullptr;

	if (Pawn)
	{
		//ÁÜÀÎ ÁÜ¾Æ¿ô
		float TargetFOV = Pawn->bIsIronSight ? IronSightFOV : NormalFOV;
		DefaultFOV = FMath::FInterpTo(DefaultFOV, TargetFOV, DeltaTime, 10.0f);
		SetFOV(DefaultFOV);

		//Ä«¸Þ¶ó ³ôÀÌ Á¶Àý
		FVector TargetOffset = Pawn->bIsCrouched ? Pawn->CrouchSpringArmPosition : TargetOffset = Pawn->NormalSpringArmPosition;
		SpringArmOffset = FMath::VInterpTo(SpringArmOffset, TargetOffset, DeltaTime, 5.0f);
		Pawn->SpringArm->SetRelativeLocation(SpringArmOffset);
	}
}
