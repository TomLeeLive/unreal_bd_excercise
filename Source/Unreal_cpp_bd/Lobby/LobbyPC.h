// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPC.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_CPP_BD_API ALobbyPC : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;
	
	class ULobbyWidgetBase* LobbyWidget;

	//UFUNCTION(Client, Reliable, WithValidation)
	UFUNCTION(Client, Reliable)
	void S2C_SetupWidget(); //Unreal Build Tool »ý¼º
	//bool S2C_SetupWidget_Validate();
	void S2C_SetupWidget_Implementation(); 

	void StartGame();

	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_SendChatMessage(const FText& SendMessage);
	bool C2S_SendChatMessage_Validate(const FText& SendMessage);
	void C2S_SendChatMessage_Implementation(const FText& SendMessage);

	UFUNCTION(Client, Reliable)
	void S2C_AddChatMessage(const FText& NewMessage);
	void S2C_AddChatMessage_Implementation(const FText& NewMessage);
};
