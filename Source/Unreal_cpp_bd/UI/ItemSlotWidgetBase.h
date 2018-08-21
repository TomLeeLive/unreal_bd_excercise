// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item/ItemDataTable.h"
#include "ItemSlotWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_CPP_BD_API UItemSlotWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UImage* ItemThumb;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UTextBlock* ItemName;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UTextBlock* ItemCount;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UButton* ItemButton;
	
	UFUNCTION(BlueprintCallable)
	void UseItem();

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	//UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int TotalItemCount = 0;

	//UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsEmpty = true;

	FItemDataTable Data;

	void SetItem(FItemDataTable NewData);
	void ClearItem();
	void AddItemCount(int AddCount);
};
