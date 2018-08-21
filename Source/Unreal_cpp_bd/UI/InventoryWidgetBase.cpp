// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryWidgetBase.h"
#include "Components/ScrollBox.h"
#include "UI/ItemSlotWidgetBase.h"

void UInventoryWidgetBase::NativeConstruct()
{
	InventoryScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("InventoryScrollBox")));

	if (InventoryScrollBox)
	{
		for (int i = 0; i < InventoryScrollBox->GetChildrenCount(); ++i)
		{
			UItemSlotWidgetBase* Slot = Cast<UItemSlotWidgetBase>(InventoryScrollBox->GetChildAt(i));

			if (Slot)
			{
				Slots.Add(Slot);
				Slot->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
}

bool UInventoryWidgetBase::InsertItem(FItemDataTable Data)
{
	UItemSlotWidgetBase* SameSlot = GetSameIDSlot(Data.ItemIndex);
	if (SameSlot)//같은 아이템 종류가 있으면 아이템 갯수만 추가
	{
		SameSlot->AddItemCount(Data.ItemCount);
		return true;
	}

	UItemSlotWidgetBase* EmptySlot = GetEmptySlot(Data.ItemIndex);

	if (EmptySlot) // 같은 아이템 종류가 없고 빈슬롯이 있음.
	{
		EmptySlot->SetItem(Data);
		return true;
	}

	//빈 슬롯이 없음
	return false;
}

UItemSlotWidgetBase * UInventoryWidgetBase::GetEmptySlot(int ItemIndex)
{
	UItemSlotWidgetBase* Result = GetSameIDSlot(ItemIndex);
	if (Result)
	{
		return Result;
	}

	//빈 슬롯 찾기
	for (auto Slot : Slots)
	{
		if (Slot->bIsEmpty)
		{
			return Slot;
		}
	}


	return nullptr;
}

UItemSlotWidgetBase * UInventoryWidgetBase::GetSameIDSlot(int ItemIndex)
{
	//C++ 14, auto
	//새로 추가될 아이템과 같은 종류의 아이템 슬롯 탐색(사용 가능한것만)
	for (auto Slot : Slots)
	{
		
		if (Slot->Data.ItemIndex == ItemIndex &&
			Slot->Data.ItemType == EItemType::Comsume)
		{
			return Slot;
		}
		
		/*
		if (Slot->Data.ItemIndex == ItemIndex)
		{
			if(Slot->Data.ItemType == EItemType::Comsume)
				return Slot;
		}
		*/
	}

	return nullptr;
}
