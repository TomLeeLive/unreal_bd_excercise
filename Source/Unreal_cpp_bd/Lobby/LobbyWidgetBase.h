// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_CPP_BD_API ULobbyWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	class UEditableTextBox* ChattingInput;
	class UScrollBox* ChattingBox;
	class UButton* StartGameButton;
	class UTextBlock* Alive;
	class UTextBlock* PublicMessage;
	
	UFUNCTION()
	void StartGame();
	
	UFUNCTION()
	void OnTextCommit(const FText & Text, ETextCommit::Type CommitMethod);
	void HideStartButton();
};
