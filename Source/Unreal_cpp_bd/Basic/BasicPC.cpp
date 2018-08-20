// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicPC.h"
#include "Basic/BasicPCM.h"
#include "UI/ItemToolTipWidgetBase.h"
#include "ConstructorHelpers.h"
#include "Components/TextBlock.h"

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
