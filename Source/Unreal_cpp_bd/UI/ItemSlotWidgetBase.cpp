// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemSlotWidgetBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/StreamableManager.h"

void UItemSlotWidgetBase::NativeConstruct()
{
	ItemThumb = Cast<UImage>(GetWidgetFromName(TEXT("ItemThumb")));
	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	ItemCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCount")));
	ItemButton = Cast<UButton>(GetWidgetFromName(TEXT("ItemButton")));

	ItemButton->OnClicked.AddDynamic(this, &UItemSlotWidgetBase::UseItem);
}

void UItemSlotWidgetBase::UseItem()
{
	if (Data.ItemType == EItemType::Comsume)
	{
		TotalItemCount--;

		//ĳ�������� ����
		//

		if (TotalItemCount == 0) // ������ ��� ���
		{
			ClearItem();
		}
		else // ������ ���� ���׷��̵�
		{
			if (ItemCount)
			{
				ItemCount->SetText(FText::FromString(FString::FromInt(TotalItemCount)));
			}
		}
	}
	else
	{
		//��� ����
		UE_LOG(LogClass, Warning, TEXT("Equip"));
	}
}

FReply UItemSlotWidgetBase::NativeOnMouseButtonDown(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
{
	//return FReply::Unhandled();
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	//������ ��ư�� Ŭ�� ������ ���.
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton) && !bIsEmpty)
	{
		UseItem();
	}

	return FReply::Handled();
}

void UItemSlotWidgetBase::SetItem(FItemDataTable NewData)
{
	if (ItemThumb)
	{
		FStreamableManager AssetLoader;
		ItemThumb->SetBrushFromTexture(AssetLoader.LoadSynchronous<UTexture2D>
			(NewData.ItemThumnail));
	}

	if (ItemName)
	{
		ItemName->SetText(FText::FromString(NewData.ItemName));
	}

	if (ItemCount)
	{
		TotalItemCount = NewData.ItemCount;
		//ItemCount->SetText(FText::FromString(FString::FromInt(TotalItemCount)));
		ItemCount->SetText(FText::FromString(FString::Printf(TEXT("x %d"), TotalItemCount)));
	}
	bIsEmpty = false;
	Data = NewData;
	SetVisibility(ESlateVisibility::Visible);
}

void UItemSlotWidgetBase::ClearItem()
{
	bIsEmpty = true;
	SetVisibility(ESlateVisibility::Collapsed);
}

void UItemSlotWidgetBase::AddItemCount(int AddCount)
{
	TotalItemCount += AddCount;

	if (ItemCount)
	{
		//ItemCount->SetText(FText::FromString(FString::FromInt(TotalItemCount)));
		ItemCount->SetText(FText::FromString(FString::Printf(TEXT("x %d"), TotalItemCount)));
	}
}
