// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyGS.h"
#include  "UnrealNetwork.h"
#include "Lobby/LobbyPC.h"
#include "LobbyWidgetBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void ALobbyGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGS, UserCount);
	DOREPLIFETIME(ALobbyGS, LeftTime);

}

void ALobbyGS::OnRep_UserCount()
{
	auto PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PC)
	{
		if (PC->LobbyWidget)
		{
			FString UserCountText = FString::Printf(TEXT("%d명 합류"), UserCount);
			PC->LobbyWidget->Alive->SetText(FText::FromString(UserCountText));
		}
	}
}

void ALobbyGS::OnRep_LeftTime()
{
	auto PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PC)
	{
		if (PC->LobbyWidget)
		{
			FString MessageText = FString::Printf(TEXT("현재 남은 시간 %d 초 입니다."), LeftTime);
			PC->LobbyWidget->PublicMessage->SetText(FText::FromString(MessageText));
		}
	}
}
