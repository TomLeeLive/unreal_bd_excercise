// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BasicAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_CPP_BD_API UBasicAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State")
	float Speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State")
	float Direction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State")
	bool bIsCrouch;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State")
	bool bIsIronsight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State")
		float AimYaw;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State")
		float AimPitch;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "State")
		bool bIsFire;
};
