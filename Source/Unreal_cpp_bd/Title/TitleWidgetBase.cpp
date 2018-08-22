// Fill out your copyright notice in the Description page of Project Settings.

#include "TitleWidgetBase.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "BDGI.h"

void UTitleWidgetBase::NativeConstruct()
{
	UserID = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("UserID")));
	ServerIP = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ServerIP")));
	StartButton = Cast<UButton>(GetWidgetFromName(TEXT("StartButton")));
	ConnectButton = Cast<UButton>(GetWidgetFromName(TEXT("ConnectButton")));

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::StartServer);
	}

	if (ConnectButton)
	{
		ConnectButton->OnClicked.AddDynamic(this, &UTitleWidgetBase::ConnectServer);
	}


	if (UserID)
	{
		FString UserName = FString::Printf(TEXT("Noname%d"), FMath::RandRange(0, 999));
		UserID->SetText(FText::FromString(UserName));
	}
}

void UTitleWidgetBase::StartServer()
{
	SetUserID();
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Lobby")), true, TEXT("listen"));
}

void UTitleWidgetBase::ConnectServer()
{
	if (ServerIP)
	{
		if (!ServerIP->GetText().IsEmpty())
		{
			SetUserID();
			UGameplayStatics::OpenLevel(GetWorld(), *ServerIP->GetText().ToString());
		}
	}
	
}

void UTitleWidgetBase::SetUserID()
{
	UBDGI* GI = Cast<UBDGI>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GI)
	{
		GI->UserID = UserID->GetText();
	}
}
