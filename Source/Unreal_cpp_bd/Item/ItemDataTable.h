// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataTable.generated.h"


UENUM(BlueprintType)
enum class EItemType : uint8
{
	Unknwon = 0		UMETA(Display = "Unknown"),
	Equip = 1		UMETA(Display =  "Equip"),
	Comsume = 2		UMETA(Display = "Comsume")
};

UENUM(BlueprintType)
enum class EEquitType : uint8
{
	NotUse = 0		UMETA(Display = "NotUse"),
	WeaponRightHand = 1		UMETA(Display = "Weapon"),
	Weapon = 2		UMETA(Display = "Weapon"),
	WeaponBack = 3		UMETA(Display = "WeaponBack01"),
};


/**
 * 
 */


USTRUCT(BlueprintType)
struct UNREAL_CPP_BD_API FItemDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	//ItemIndex	ItemName	ItemType	ItemEquipSlot	ItemFloat01	ItemCount	ItemThumnail	ItemMesh
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ItemIndex;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EItemType ItemType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EEquitType ItemEquipSlot;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ItemFloat01;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ItemCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TAssetPtr<class UTexture2D> ItemThumnail;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TAssetPtr<class UStaticMesh> ItemMesh;

	
};
