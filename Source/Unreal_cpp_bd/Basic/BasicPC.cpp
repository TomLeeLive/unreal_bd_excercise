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
	
	//BP를 경로 읽어 오기(실행중에)
	FStringClassReference ItemTooltipWidgetClass(TEXT("WidgetBlueprint'/Game/UI/ItemTooltipWidget.ItemTooltipWidget_C'"));

	//위 경로로 위젯 클래스를 CDO에 생성
	if (UClass* MyWidgetClass = ItemTooltipWidgetClass.TryLoadClass<UUserWidget>())
	{
		//C++ Class로 인스턴스 생성, CDO에 있는 오브젝트를 실제로 생성(복사)
		 ItemTooltipWidget = Cast<UItemToolTipWidgetBase>(CreateWidget<UUserWidget>(this, MyWidgetClass));

		 //UI를 화면에 붙이기
		 ItemTooltipWidget->AddToViewport();
		 ItemTooltipWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	//BP를 경로 읽어 오기(실행중에)
	FStringClassReference InventoryWidgetClass(TEXT("WidgetBlueprint'/Game/UI/InventoryWidget.InventoryWidget_C'"));

	//위 경로로 위젯 클래스를 CDO에 생성
	if (UClass* MyWidgetClass = InventoryWidgetClass.TryLoadClass<UUserWidget>())
	{
		//C++ Class로 인스턴스 생성, CDO에 있는 오브젝트를 실제로 생성(복사)
		InventoryWidget = Cast<UInventoryWidgetBase>(CreateWidget<UUserWidget>(this, MyWidgetClass));

		//UI를 화면에 붙이기
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
		SetInputMode(FInputModeGameAndUI()); // PC->Pawn Input Process, key 전달, 마우스 전달 X
	}
	else
	{
		InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}
}
