// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicPC.h"
#include "Basic/BasicPCM.h"
#include "UI/ItemToolTipWidgetBase.h"
#include "ConstructorHelpers.h"
#include "Components/TextBlock.h"
#include "UI/InventoryWidgetBase.h"

ABasicPC::ABasicPC()
{
	PlayerCameraManagerClass = ABasicPCM::StaticClass();

	/*
	static ConstructorHelpers::FClassFinder<UUserWidget>WidgetClassRef(TEXT("WidgetBlueprint'/Game/UI/ItemTooltipWidget.ItemTooltipWidget_C'"));

	if (WidgetClassRef.Succeeded)
	{
		WidgetClass = WidgetClassRef.Class;
	}
	*/
}

void ABasicPC::BeginPlay()
{
	
	//BP�� ��� �о� ����(�����߿�)
	FStringClassReference ItemTooltipWidgetClass(TEXT("WidgetBlueprint'/Game/UI/ItemTooltipWidget.ItemTooltipWidget_C'"));

	//�� ��η� ���� Ŭ������ CDO�� ����
	if (UClass* MyWidgetClass = ItemTooltipWidgetClass.TryLoadClass<UUserWidget>())
	{
		//C++ Class�� �ν��Ͻ� ����, CDO�� �ִ� ������Ʈ�� ������ ����(����)
		 ItemTooltipWidget = Cast<UItemToolTipWidgetBase>(CreateWidget<UUserWidget>(this, MyWidgetClass));

		 //UI�� ȭ�鿡 ���̱�
		 ItemTooltipWidget->AddToViewport();
		 ItemTooltipWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	//BP�� ��� �о� ����(�����߿�)
	FStringClassReference InventoryWidgetClass(TEXT("WidgetBlueprint'/Game/UI/InventoryWidget.InventoryWidget_C'"));

	//�� ��η� ���� Ŭ������ CDO�� ����
	if (UClass* MyWidgetClass = InventoryWidgetClass.TryLoadClass<UUserWidget>())
	{
		//C++ Class�� �ν��Ͻ� ����, CDO�� �ִ� ������Ʈ�� ������ ����(����)
		InventoryWidget = Cast<UInventoryWidgetBase>(CreateWidget<UUserWidget>(this, MyWidgetClass));

		//UI�� ȭ�鿡 ���̱�
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	

	/*
	if (WidgetClass)
	{
		ItemTooltipWidget = Cast<UItemTooltipWidgetBase>(CreateWidget<UUserWidget>(this, WidgetClass));

		ItemTooltipWidget->AddToViewport();
	}
	*/
	/*
	if (WidgetClass)
	{
		ItemTooltipWidget = Cast<UItemTooltipWidgetBase>(NewObject<UUserWidget>(this, WidgetClass));

		ItemTooltipWidget->AddToViewport();
	}
	*/
}

void ABasicPC::SetItemName(FString ItemName)
{
	if (ItemTooltipWidget && ItemTooltipWidget->ItemName)
	{
		ItemTooltipWidget->ItemName->SetText(FText::FromString(ItemName));
	}
}

void ABasicPC::ShowItemToolTip(bool bShow)
{
	if (ItemTooltipWidget)
	{
		if (bShow)
		{
			ItemTooltipWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			ItemTooltipWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

}

void ABasicPC::ToggleInventory()
{
	if (InventoryWidget->GetVisibility() == ESlateVisibility::Collapsed)
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		bShowMouseCursor = true;
		SetInputMode(FInputModeGameAndUI()); // PC->Pawn Input Process, key ����, ���콺 ���� X
	}
	else
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}
}
