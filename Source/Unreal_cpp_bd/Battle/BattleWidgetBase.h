// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_CPP_BD_API UBattleWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	class UTextBlock* AliveCount;
	class UTextBlock* PublicMessage;
	class UScrollBox* Info;
	class UProgressBar* HPBar;

	virtual void NativeConstruct() override;
	void AddInfo(FString Message);

	UFUNCTION()
	void DeleteInfo();
};
