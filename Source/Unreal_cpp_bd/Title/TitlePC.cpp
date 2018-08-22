// Fill out your copyright notice in the Description page of Project Settings.

#include "TitlePC.h"
#include "Title/TitleWidgetBase.h"

void ATitlePC::BeginPlay()
{
	//BP�� ��� �о� ����(�����߿�)
	FStringClassReference TitleWidgetClass(TEXT("WidgetBlueprint'/Game/UI/Title/TitleWidget.TitleWidget_C'"));

	//�� ��η� ���� Ŭ������ CDO�� ����
	if (UClass* MyWidgetClass = TitleWidgetClass.TryLoadClass<UUserWidget>())
	{
		//C++ Class�� �ν��Ͻ� ����, CDO�� �ִ� ������Ʈ�� ������ ����(����)
		UTitleWidgetBase* TitleWidget = Cast<UTitleWidgetBase>(CreateWidget<UUserWidget>(this, MyWidgetClass));

		//UI�� ȭ�鿡 ���̱�
		TitleWidget->AddToViewport();
		//TitleWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
