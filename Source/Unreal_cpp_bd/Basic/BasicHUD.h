// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BasicHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_CPP_BD_API ABasicHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ABasicHUD();
	
	virtual void DrawHUD() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UTexture2D* Crosshair;
};
