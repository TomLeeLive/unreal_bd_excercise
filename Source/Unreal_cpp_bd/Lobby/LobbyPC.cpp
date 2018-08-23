// Fill out your copyright notice in the Description page of Project Settings.

#include "LobbyPC.h"
#include "Lobby/LobbyWidgetBase.h"
void ALobbyPC::BeginPlay()
{
	S2C_SetupWidget();
}

/*
bool ALobbyPC::S2C_SetupWidget_Validate()
{
	return true;
}
*/

void ALobbyPC::S2C_SetupWidget_Implementation()
{
	//BP�� ��� �о� ����(�����߿�)
	FStringClassReference LobbyWidgetClassRef(TEXT("WidgetBlueprint'/Game/UI/Lobby/LobbyWidget.LobbyWidget_C'"));
	//FStringClassReference TitleWidgetClass(TEXT("WidgetBlueprint'/Game/UI/Title/TitleWidget.TitleWidget_C'"));

	//�� ��η� ���� Ŭ������ CDO�� ����
	if (UClass* MyWidgetClass = LobbyWidgetClassRef.TryLoadClass<UUserWidget>())
	{
		//C++ Class�� �ν��Ͻ� ����, CDO�� �ִ� ������Ʈ�� ������ ����(����)
		LobbyWidget = Cast<ULobbyWidgetBase>(CreateWidget<UUserWidget>(this, MyWidgetClass));

		//UI�� ȭ�鿡 ���̱�
		LobbyWidget->AddToViewport();
		//TitleWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;

	if (!HasAuthority()) // Client
	{
		LobbyWidget->HideStartButton();
	}
}

void ALobbyPC::StartGame()
{
	GetWorld()->ServerTravel(TEXT("Battle"));
}

/*
void ALobbyPC::C2S_SendChatMessage(const FText & SendMessage)
{
}
*/
bool ALobbyPC::C2S_SendChatMessage_Validate(const FText & SendMessage)
{
	return true;
}

void ALobbyPC::C2S_SendChatMessage_Implementation(const FText & SendMessage)
{
	//UE_LOG(LogClass, Warning, TEXT("EEEEEEEEEEEEEEEEE"), );

	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		ALobbyPC* PC = Cast<ALobbyPC>(*Iter);
		
		if (PC)
		{
			//UE_LOG(LogClass, Warning, TEXT("FFFFFFFFFFFF"), );
			PC->S2C_AddChatMessage(SendMessage);
		}
	}
}

void ALobbyPC::S2C_AddChatMessage_Implementation(const FText & NewMessage)
{
	if (LobbyWidget)
	{
		LobbyWidget->AddChatMessage(NewMessage);
		//UE_LOG(LogClass, Warning, TEXT("GGGGGGGGGGGGG"), );

		//UE_LOG(LogClass, Warning, TEXT("%s"), *NewMessage.ToString());
	}
}
