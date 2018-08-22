// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyWidgetBase.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"

#include "Lobby/LobbyPC.h"
#include "Kismet/GameplayStatics.h"

#include "BDGI.h"

void ULobbyWidgetBase::NativeConstruct()
{
	Alive = Cast<UTextBlock>(GetWidgetFromName(TEXT("Alive")));
	PublicMessage = Cast<UTextBlock>(GetWidgetFromName(TEXT("PublicMessage")));
	ChattingInput = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ChattingInput")));
	StartGameButton = Cast<UButton>(GetWidgetFromName(TEXT("StartGameButton")));
	ChattingBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("ChattingBox")));


	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &ULobbyWidgetBase::StartGame);
	}

	if (ChattingInput)
	{
		//UE_LOG(LogClass, Warning, TEXT("fffffffffffffffffffffffffffff"), );

		ChattingInput->OnTextCommitted.AddDynamic(this, &ULobbyWidgetBase::OnTextCommit);
	}
}

void  ULobbyWidgetBase::StartGame()
{
	ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PC)
	{
		PC->StartGame();
	}
}

void  ULobbyWidgetBase::OnTextCommit(const FText& Text, ETextCommit::Type CommitMethod)
{
	ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	//UE_LOG(LogClass, Warning, TEXT("AAAAAAAAAAAAAAAAAAA"), );
	if (PC)
	{
		//UE_LOG(LogClass, Warning, TEXT("BBBBBBBBBB"), );

		if (CommitMethod == ETextCommit::OnEnter)
		{
			//UE_LOG(LogClass, Warning, TEXT("CCCCCCCCCCC"), );
			if (Text.IsEmpty())
			{
				//채팅 끝
			}
			else
			{
				//채팅 전송
				auto GI = Cast<UBDGI>(UGameplayStatics::GetGameInstance(GetWorld()));
				
				if (GI)
				{
					//UE_LOG(LogClass, Warning, TEXT("DDDDDDDDDDDDDD"), );

					FString Message = FString::Printf(TEXT("%s : %s"), *GI->UserID.ToString(), *Text.ToString());
					PC->C2S_SendChatMessage(FText::FromString(Message));
				}
			}
		}
	}
}

void  ULobbyWidgetBase::HideStartButton()
{
	if (StartGameButton)
	{
		StartGameButton->SetVisibility(ESlateVisibility::Collapsed);
	}

}