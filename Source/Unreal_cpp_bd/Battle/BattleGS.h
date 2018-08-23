// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BattleGS.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_CPP_BD_API ABattleGS : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_AliveCount)
	int AliveCount = 0;

	UFUNCTION()
	void OnRep_AliveCount();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
