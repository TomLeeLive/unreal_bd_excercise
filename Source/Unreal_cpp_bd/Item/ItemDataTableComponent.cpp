// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemDataTableComponent.h"

#include "Item/ItemDataTable.h"
#include "ConstructorHelpers.h"

// Sets default values for this component's properties
UItemDataTableComponent::UItemDataTableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ItemTable(TEXT("DataTable'/Game/Data/ItemTable.ItemTable'"));
	if (DT_ItemTable.Succeeded())
	{
		DataTable = DT_ItemTable.Object;
	}
}

const FItemDataTable & UItemDataTableComponent::GetItemData(int ItemIndex)
{
	return *DataTable->FindRow<FItemDataTable>(*FString::FromInt(ItemIndex), TEXT("ItemIndex"));
}

