// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemToolTipWidgetBase.h"
#include "Components/TextBlock.h"

void UItemToolTipWidgetBase::NativeConstruct()
{
	//���� �������Ʈ���� ������ ������ C++������ ����
	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
}
