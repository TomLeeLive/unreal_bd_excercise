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
	//BP를 경로 읽어 오기(실행중에)
	FStringClassReference LobbyWidgetClassRef(TEXT("WidgetBlueprint'/Game/UI/Lobby/LobbyWidget.LobbyWidget_C'"));
	//FStringClassReference TitleWidgetClass(TEXT("WidgetBlueprint'/Game/UI/Title/TitleWidget.TitleWidget_C'"));

	//위 경로로 위젯 클래스를 CDO에 생성
	if (UClass* MyWidgetClass = LobbyWidgetClassRef.TryLoadClass<UUserWidget>())
	{
		//C++ Class로 인스턴스 생성, CDO에 있는 오브젝트를 실제로 생성(복사)
		LobbyWidget = Cast<ULobbyWidgetBase>(CreateWidget<UUserWidget>(this, MyWidgetClass));

		//UI를 화면에 붙이기
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
