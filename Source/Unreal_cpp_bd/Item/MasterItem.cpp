// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterItem.h"

#include "Components/SphereComponent.h"
#include "Item/ItemDataTableComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StreamableManager.h"



//����� ��Ʈ�� �������[Start]
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"
//����� ��Ʈ�� �������[End]

#include "Basic/BasicPlayer.h"

// Sets default values
AMasterItem::AMasterItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
	Sphere->SetSphereRadius(200.0f, true);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	DataTable = CreateDefaultSubobject<UItemDataTableComponent>(TEXT("DataTable"));
}

// Called when the game starts or when spawned
void AMasterItem::BeginPlay()
{
	Super::BeginPlay();
	
	//����� ��Ʈ�� �������[Start]
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(100,
			5.0f,
			FColor::Red,
			TEXT("HelloWorld"));
	}

	UKismetSystemLibrary::PrintString(GetWorld());
	//����� ��Ʈ�� �������[End]

	if (DataTable && DataTable->DataTable)
	{
		//������ �ε����� ���� �ε�
		ItemIndex = FMath::RandRange(1, 6) * 10;
		
		Data = DataTable->GetItemData(ItemIndex);
		ItemCount = Data.ItemCount;

		FStreamableManager AssetLoader;
		StaticMesh->SetStaticMesh(AssetLoader.LoadSynchronous<UStaticMesh>(Data.ItemMesh));
		//	AssetLoader.RequestAsyncLoad(Data.ItemMesh.ToSoftObjectPath(),&AMasterItem::AsyncLoadComplete);


		//�浹����
		Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMasterItem::OnBeginOverlap);
		Sphere->OnComponentEndOverlap.AddDynamic(this, &AMasterItem::OnEndOverlap);
	}
}

void AMasterItem::AsyncLoadComplete(TSharedRef<struct FStreamableHandle> Data)
{

}

void AMasterItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OthreComp,
	int32 OtherBodyIndex)
{
	ABasicPlayer* Pawn = Cast<ABasicPlayer>(OtherActor);
	if (Pawn)
	{
		Pawn->RemovePickupItemList(this);
		UE_LOG(LogClass, Warning, TEXT("Remove"));
	}
}
void AMasterItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OthreComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	ABasicPlayer* Pawn = Cast<ABasicPlayer>(OtherActor);
	if (Pawn)
	{
		Pawn->AddPickupItemList(this);
		UE_LOG(LogClass,Warning, TEXT("Add"));
	}
}

// Called every frame
void AMasterItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

