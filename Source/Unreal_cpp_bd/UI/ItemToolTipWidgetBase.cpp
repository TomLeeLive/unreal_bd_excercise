// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemToolTipWidgetBase.h"
#include "Components/TextBlock.h"

void UItemToolTipWidgetBase::NativeConstruct()
{
	//위젯 블루프린트에서 생성한 위젯을 C++변수와 연결
	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
}
