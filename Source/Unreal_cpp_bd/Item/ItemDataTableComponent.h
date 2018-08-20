// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/ItemDataTable.h"
#include "ItemDataTableComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_CPP_BD_API UItemDataTableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemDataTableComponent();

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataTable")
	class UDataTable* DataTable;

	UFUNCTION(BlueprintCallable, Category = "DataTable")
	const FItemDataTable& GetItemData(int ItemIndex) ;

	
};
