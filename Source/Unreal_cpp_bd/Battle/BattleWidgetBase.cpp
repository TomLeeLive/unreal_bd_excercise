// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleWidgetBase.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/ScrollBox.h"
#include "Engine/World.h"
#include "TimerManager.h"

void UBattleWidgetBase::NativeConstruct()
{
	AliveCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("AliveCount")));
	PublicMessage = Cast<UTextBlock>(GetWidgetFromName(TEXT("PublicMessage")));
	Info = Cast<UScrollBox>(GetWidgetFromName(TEXT("Info")));
	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
}

void UBattleWidgetBase::AddInfo(FString Message)
{
	if (Info)
	{
		UTextBlock* NewMessage = NewObject<UTextBlock>(Info);

		if (NewMessage)
		{
			NewMessage->SetJustification(ETextJustify::Right);
			NewMessage->SetText(FText::FromString(Message));
			Info->AddChild(NewMessage);

			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle,
				this,
				&UBattleWidgetBase::DeleteInfo,
				3.0f,
				false);

		}
	}
}

void UBattleWidgetBase::DeleteInfo()
{
	if (Info)
	{
		if (Info->GetChildrenCount() > 0)
		{
			Info->RemoveChildAt(0);
		}
	}
}