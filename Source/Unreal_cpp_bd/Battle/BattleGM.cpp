// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGM.h"
#include "BattleGS.h"
ABattleGM::ABattleGM()
{
	bUseSeamlessTravel = true; //BP에서 Use Seamless Travel 체크와 같은것.
}

//Not Seamless Travel 인경 호출, 첫 접속
void ABattleGM::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	ABattleGS* GS = GetGameState<ABattleGS>();

	if (GS)
	{

		GS->AliveCount = GS->PlayerArray.Num();
		//Host 강제 실행
		GS->OnRep_AliveCount();
	}
}
//Seamless Travel 인경 호출
void ABattleGM::HandleStartingNewPlayer(APlayerController * NewPlayer)
{
	UE_LOG(LogClass, Warning, TEXT("Add Player"));
}
