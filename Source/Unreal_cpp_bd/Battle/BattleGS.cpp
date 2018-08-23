// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleGS.h"
#include "Battle/BattlePC.h"
#include "Battle/BattleWidgetBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "UnrealNetwork.h"

void ABattleGS::OnRep_AliveCount()
{
	//위젯 업데이트
	auto PC = Cast<ABattlePC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		if (PC->BattleWidget)
		{
			FString NewMessage = FString::Printf(TEXT("%d 생존"), AliveCount);
			PC->BattleWidget->AliveCount->SetText(FText::FromString(NewMessage));
		}
	}
}

void ABattleGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABattleGS, AliveCount);

}
