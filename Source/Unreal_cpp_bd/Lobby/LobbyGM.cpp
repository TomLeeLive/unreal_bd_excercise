// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGM.h"
#include "LobbyGS.h"
#include "Engine/World.h"
#include "TimerManager.h"

void ALobbyGM::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		StartTimer,
		this,
		&ALobbyGM::DecreaseTime,
		1.0f,
		true,
		0.0f
	);
}

void ALobbyGM::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);
	ALobbyGS* GS = GetGameState<ALobbyGS>();

	if (GS)
	{
		//유저 카운트 방법

		//1
		//GS->UserCount++;
	
		//2
		/*
		GS->UserCount = 0;
		for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
		{
			GS->UserCount++;
		}
		*/

		//3
		GS->UserCount = GS->PlayerArray.Num();

		UE_LOG(LogClass, Warning, TEXT("UserCount: %d"), GS->UserCount);

		//Host 강제 실행
		GS->OnRep_UserCount();
	}
}

void ALobbyGM::DecreaseTime()
{
	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		GS->LeftTime--;
		if (HasAuthority()) // GameMode의 권한을 가진건 Host
		{
			GS->OnRep_LeftTime(); // Client들은 자동 호출이 되지만 Host는 호출이 안됨, 강제 호출
			
			if (GS->LeftTime < 0)
			{
				GetWorldTimerManager().ClearTimer(StartTimer);
				//배틀맵으로 이동

			}
		}
	}
}
