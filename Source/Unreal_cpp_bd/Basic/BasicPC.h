// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicPC.generated.h"
/**
 * 
 */
UCLASS()
class UNREAL_CPP_BD_API ABasicPC : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	ABasicPC();
	
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UItemToolTipWidgetBase* ItemTooltipWidget;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UInventoryWidgetBase* InventoryWidget;

	//BP�� ���� �������Ʈ Ŭ������ �޴� ����
	TSubclassOf<UUserWidget> WidgetClass;

	UFUNCTION(BlueprintCallable)
	void SetItemName(FString ItemName);

	UFUNCTION(BlueprintCallable)
	void ShowItemToolTip(bool bShow);

	void ToggleInventory();
};
