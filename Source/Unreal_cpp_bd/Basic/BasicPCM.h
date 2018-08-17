// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "BasicPCM.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_CPP_BD_API ABasicPCM : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	ABasicPCM();

	virtual void BeginPlay() override;

	virtual void UpdateCamera(float DeltaTime) override;
	
	FVector SpringArmOffset;

	float DefaultFOV;

	float NormalFOV = 90.0f;
	float IronSightFOV = 45.0f;
};
