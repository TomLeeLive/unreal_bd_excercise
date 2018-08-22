// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BDGI.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_CPP_BD_API UBDGI : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText UserID;
	
	
};
