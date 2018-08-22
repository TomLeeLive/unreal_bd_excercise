// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_CPP_BD_API UTitleWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UEditableTextBox* UserID;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UEditableTextBox* ServerIP;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UButton* StartButton;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UButton* ConnectButton;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString UserIdName;

	UFUNCTION()
	void StartServer();

	UFUNCTION()
	void ConnectServer();
	void SetUserID();
};
