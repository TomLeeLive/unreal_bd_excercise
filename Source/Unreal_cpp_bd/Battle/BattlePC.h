// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattlePC.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_CPP_BD_API ABattlePC : public APlayerController
{
	GENERATED_BODY()

public:
		ABattlePC();

	virtual void BeginPlay() override;

	UFUNCTION(Client, Reliable)
	void S2C_SetupWidget();
	void S2C_SetupWidget_Implementation();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UItemToolTipWidgetBase* ItemTooltipWidget;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UInventoryWidgetBase* InventoryWidget;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		class UBattleWidgetBase* BattleWidget;

	UFUNCTION(BlueprintCallable)
		void SetItemName(FString ItemName);

	UFUNCTION(BlueprintCallable)
		void ShowItemToolTip(bool bShow);

	void ToggleInventory();
	
	
};
