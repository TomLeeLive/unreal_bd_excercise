// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item/ItemDataTable.h"
#include "MasterItem.generated.h"


UCLASS()
class UNREAL_CPP_BD_API AMasterItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AsyncLoadComplete(TSharedRef<struct FStreamableHandle> Data);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OthreComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OthreComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	class USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UItemDataTableComponent* DataTable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category  ="Data")
	int ItemIndex;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	int ItemCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Data")
	FItemDataTable Data;
};
