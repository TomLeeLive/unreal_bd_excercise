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
	if (SameSlot)//���� ������ ������ ������ ������ ������ �߰�
	{
		SameSlot->AddItemCount(Data.ItemCount);
		return true;
	}

	UItemSlotWidgetBase* EmptySlot = GetEmptySlot(Data.ItemIndex);

	if (EmptySlot) // ���� ������ ������ ���� �󽽷��� ����.
	{
		EmptySlot->SetItem(Data);
		return true;
	}

	//�� ������ ����
	return false;
}

UItemSlotWidgetBase * UInventoryWidgetBase::GetEmptySlot(int ItemIndex)
{
	UItemSlotWidgetBase* Result = GetSameIDSlot(ItemIndex);
	if (Result)
	{
		return Result;
	}

	//�� ���� ã��
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
	//���� �߰��� �����۰� ���� ������ ������ ���� Ž��(��� �����Ѱ͸�)
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
