// Fill out your copyright notice in the Description page of Project Settings.

#include "TitlePC.h"
#include "Title/TitleWidgetBase.h"

void ATitlePC::BeginPlay()
{
	//BP를 경로 읽어 오기(실행중에)
	FStringClassReference TitleWidgetClass(TEXT("WidgetBlueprint'/Game/UI/Title/TitleWidget.TitleWidget_C'"));

	//위 경로로 위젯 클래스를 CDO에 생성
	if (UClass* MyWidgetClass = TitleWidgetClass.TryLoadClass<UUserWidget>())
	{
		//C++ Class로 인스턴스 생성, CDO에 있는 오브젝트를 실제로 생성(복사)
		UTitleWidgetBase* TitleWidget = Cast<UTitleWidgetBase>(CreateWidget<UUserWidget>(this, MyWidgetClass));

		//UI를 화면에 붙이기
		TitleWidget->AddToViewport();
		//TitleWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
