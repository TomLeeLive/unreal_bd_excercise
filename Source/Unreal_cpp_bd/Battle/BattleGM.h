// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleGM.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_CPP_BD_API ABattleGM : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ABattleGM();
	
	//Not Seamless
	virtual void PostLogin(APlayerController* NewPlayer) override;

	//Seamless Load
	virtual void HandleStartingNewPlayer(APlayerController* NewPlayer);
	
};
