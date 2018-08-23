// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGM.h"
#include "BattleGS.h"
ABattleGM::ABattleGM()
{
	bUseSeamlessTravel = true; //BP���� Use Seamless Travel üũ�� ������.
}

//Not Seamless Travel �ΰ� ȣ��, ù ����
void ABattleGM::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	ABattleGS* GS = GetGameState<ABattleGS>();

	if (GS)
	{

		GS->AliveCount = GS->PlayerArray.Num();
		//Host ���� ����
		GS->OnRep_AliveCount();
	}
}
//Seamless Travel �ΰ� ȣ��
void ABattleGM::HandleStartingNewPlayer(APlayerController * NewPlayer)
{
	UE_LOG(LogClass, Warning, TEXT("Add Player"));
}
