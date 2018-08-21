// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/ItemDataTable.h"
#include "InventoryWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_CPP_BD_API UInventoryWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UScrollBox* InventoryScrollBox;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<class UItemSlotWidgetBase*> Slots;

	bool InsertItem(FItemDataTable Data);

protected:
	class UItemSlotWidgetBase* GetEmptySlot(int ItemIndex);

	class UItemSlotWidgetBase* GetSameIDSlot(int ItemIndex);
};
