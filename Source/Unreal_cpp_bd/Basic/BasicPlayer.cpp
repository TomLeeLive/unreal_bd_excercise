// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "ConstructorHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Basic/WeaponComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TimerManager.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "Materials/MaterialInstance.h"
#include "Components/DecalComponent.h"
#include "Basic/RifleCameraShake.h"
#include "Basic/BasicDamageType.h"
#include "Item/MasterItem.h"
#include "Basic/BasicPC.h"
//#include "UI/ItemToolTipWidgetBase.h"

// Sets default values
ABasicPlayer::ABasicPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//메시 세팅
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Male(TEXT("SkeletalMesh'/Game/Male_Grunt/Mesh/male_grunt.male_grunt'"));

	if (SK_Male.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Male.Object);
	}

	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));
	GetMesh()->SetRelativeLocation(FVector(0, 0,-88.0f));

	//애니메이션 블루 프린트 세팅
	static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_Male(TEXT("AnimBlueprint'/Game/BluePrints/Basic/Animation/ABP_Male.ABP_Male_C'"));
	if (ABP_Male.Succeeded())
	{
		GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GetMesh()->SetAnimInstanceClass(ABP_Male.Class);
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 150.0f;
	SpringArm->SetRelativeLocation(FVector(0, 30, 70));


	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;


	Weapon = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), FName(TEXT("RHandWeapon")));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_M4A1(TEXT("StaticMesh'/Game/Weapons/M4A1/SM_M4A1.SM_M4A1'"));

	if (SM_M4A1.Succeeded())
	{
		Weapon->SetStaticMesh(SM_M4A1.Object);
	}
	
	
	static  ConstructorHelpers::FObjectFinder<UParticleSystem> P_HitEffect(TEXT("ParticleSystem'/Game/Effects/P_AssaultRifle_IH.P_AssaultRifle_IH'"));

	if (P_HitEffect.Succeeded())
	{
		HitEffect = P_HitEffect.Object;
	}

	static  ConstructorHelpers::FObjectFinder<UParticleSystem> P_BloodEffect(TEXT("ParticleSystem'/Game/Effects/P_body_bullet_impact.P_body_bullet_impact'"));

	if (P_BloodEffect.Succeeded())
	{
		BloodEffect = P_BloodEffect.Object;
	}

	static  ConstructorHelpers::FObjectFinder<UParticleSystem> P_MuzzleFlash(TEXT("ParticleSystem'/Game/Effects/P_AssaultRifle_MF.P_AssaultRifle_MF'"));

	if (P_MuzzleFlash.Succeeded())
	{
		MuzzleFlash = P_MuzzleFlash.Object;
	}

	static  ConstructorHelpers::FObjectFinder<USoundBase> S_ShootSound(TEXT("SoundCue'/Game/Sound/Weapons/SMG_Thompson/Cue_Thompson_Shot.Cue_Thompson_Shot'"));

	if (S_ShootSound.Succeeded())
	{
		ShootSound = S_ShootSound.Object;
	}

	static  ConstructorHelpers::FObjectFinder<UMaterialInstance> M_BulletDecal(TEXT("MaterialInstanceConstant'/Game/Effects/Decal/M_BulletDecal_Inst.M_BulletDecal_Inst'"));

	if (M_BulletDecal.Succeeded())
	{
		BulletDecal = M_BulletDecal.Object;
	}


	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	//GetMesh()->SetAnimInstanceClass();

	//GetCharacterMovement()->CrouchedHalfHeight = 88.0f;
	GetCharacterMovement()->CrouchedHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

	NormalSpringArmPosition = SpringArm->GetRelativeTransform().GetLocation();
	CrouchSpringArmPosition = FVector(NormalSpringArmPosition.X,
		NormalSpringArmPosition.Y,
		NormalSpringArmPosition.Z - 40.0f);

}

// Called when the game starts or when spawned
void ABasicPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHP = MaxHP;
}

// Called every frame
void ABasicPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &ABasicPlayer::Pitch);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &ABasicPlayer::Yaw);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &ABasicPlayer::Forward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &ABasicPlayer::Right);

	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &ABasicPlayer::TryCrouch);
	PlayerInputComponent->BindAction(TEXT("Ironsight"), IE_Pressed, this, &ABasicPlayer::TryIronsight);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ABasicPlayer::StartFire);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &ABasicPlayer::StopFire);
	//PlayerInputComponent->BindAction(TEXT("Fire"), IE_Repeat, this, &ABasicPlayer::Fire);
}

void ABasicPlayer::Pitch(float value)
{
	if (value != 0.0f)
	{
		AddControllerPitchInput(value);
	}
}

void ABasicPlayer::Yaw(float value)
{
	if (value != 0.0f)
	{
		AddControllerYawInput(value);
	}
}

void ABasicPlayer::Forward(float value)
{
	if (value != 0.0f)
	{
		//카메라의 Yaw 성분만 이용해서 방향 벡터 만들기, 화면에서 앞쪽 방향
		FRotator Rotation = GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);
		AddMovementInput(UKismetMathLibrary::GetForwardVector(YawRotation), value);

		//액터의 앞방향
		//AddMovementInput(GetActorForwardVector(), value);

		//절대회전의 앞방향, 카메라가 보는 방향
		//AddMovementInput(UKismetMathLibrary::GetForwardVector(GetControlRotation()), value);
		
	}
}

void ABasicPlayer::Right(float value)
{
	if (value != 0.0f)
	{
		FRotator Rotation = GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);
		AddMovementInput(UKismetMathLibrary::GetRightVector(YawRotation), value);

		//AddMovementInput(GetActorRightVector(), value);
		//AddMovementInput(UKismetMathLibrary::GetRightVector(GetControlRotation()), value);
	}
}

void ABasicPlayer::TryCrouch()
{
	if (CanCrouch())
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void ABasicPlayer::TryIronsight()
{
	bIsIronSight = bIsIronSight ? false : true;
	// 조준중에는 걷는 속도
}

void ABasicPlayer::StartFire()
{
	bIsFire = true;
	Shoot();
}

void ABasicPlayer::StopFire()
{
	bIsFire = false;
}

void ABasicPlayer::Shoot()
{
	if (!bIsFire)
	{
		return;
	}

	//3차원 공간의 카메라 위치와 회전
	FVector CameraLocation;
	FRotator CameraRotation;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerViewPoint(CameraLocation, CameraRotation);

	//화면 좌표계 크기 가져오기
	int SizeX;
	int SizeY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(SizeX, SizeY);

	//화면 가운데 2D-> 3D 변환 (카메라를 기준, 플레이 컨트롤러)
	FVector CrosshairWorldLocation;
	FVector CrosshairWorldDirection;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectScreenPositionToWorld(SizeX / 2, SizeY / 2, CrosshairWorldLocation, CrosshairWorldDirection);

	FVector TraceStart = CameraLocation;
	FVector TraceEnd = CameraLocation + (CrosshairWorldDirection * 80000.0f);

	//광선 추적에 대한 정보 세팅
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	TArray<AActor*> IgnoreActors;
	FHitResult OutHit;

	ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	IgnoreActors.Add(this);

	//광선 추적
	bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(),
		TraceStart,		//트레이스 시작점
		TraceEnd,		//트레이스 끝점
		ObjectType,		//트레이싱 검출 될 오브젝트 타입들
		false,			//복합 컬리전 사용 여부
		IgnoreActors,	// 무시 액터 리스트
		EDrawDebugTrace::None,//EDrawDebugTrace::ForDuration, //디버그 라인 그리기 설정
		OutHit,			//충돌 정보
		true,			//자기 자신 제외
		FLinearColor::Red,	//디버그 라인 색깔.
		FLinearColor::Blue, //충돌 지역 디버그 박스 색깔.
		5.0					//디버그 라인 그리는 시간.
	);


	if (Result)
	{
	TraceStart = Weapon->GetSocketLocation(FName(TEXT("MuzzleFlash")));
	FVector Dir = OutHit.ImpactPoint - TraceStart;
	TraceEnd = TraceStart + (Dir * 2.0f);

	//광선 추적
	Result = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(),
		TraceStart,		//트레이스 시작점
		TraceEnd,		//트레이스 끝점
		ObjectType,		//트레이싱 검출 될 오브젝트 타입들
		true,			//복합 컬리전 사용 여부
		IgnoreActors,	// 무시 액터 리스트
		EDrawDebugTrace::None,//EDrawDebugTrace::ForDuration, //디버그 라인 그리기 설정
		OutHit,			//충돌 정보
		true,			//자기 자신 제외
		FLinearColor::Green,	//디버그 라인 색깔.
		FLinearColor::Blue, //충돌 지역 디버그 박스 색깔.
		5.0					//디버그 라인 그리는 시간.
	);

	//총구 끝에서 총알이 나가서 맞았는지 확인
	if (Result)
	{
		/*
		UGameplayStatics::ApplyRadialDamage(GetWorld(),
			100.0f,
			OutHit.ImpactPoint,
			300.0f,
			UBasicDamageType::StaticClass(),
			IgnoreActors,
			this,
			GetController()
		);
		*/
		APawn* Hitter = Cast<APawn>(OutHit.GetActor());

		if (Hitter)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
				BloodEffect, OutHit.ImpactPoint, FRotator::ZeroRotator);

			UGameplayStatics::ApplyPointDamage(OutHit.GetActor(),
				30.0f,
				TraceEnd - TraceStart,
				OutHit,
				GetController(),
				this,
				UBasicDamageType::StaticClass());
		}
		else
		{
			//탄흔 이펙트
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
				HitEffect, OutHit.ImpactPoint, FRotator::ZeroRotator);

			//총알 구멍, 데칼
			UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),
				BulletDecal,
				FVector(0.3f, 5.0f, 5.0f),
				OutHit.ImpactPoint, OutHit.ImpactNormal.Rotation(), 10.0f);

			Decal->SetFadeScreenSize(0.01f); //화면이 차지하는 비율보다 작으면 안보이게
		}

	}

	}

	//반동 카메라 흔들기
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->PlayCameraShake(URifleCameraShake::StaticClass());

	//총구 방향 반동 주기
	FRotator CurrentRotation = GetControlRotation();
	CurrentRotation.Pitch += 2.0f;
	CurrentRotation.Yaw += FMath::RandRange(-1.5f, 1.5f);
	GetController()->SetControlRotation(CurrentRotation);

	//총소리
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(),
		ShootSound, Weapon->GetComponentLocation(),
		Weapon->GetComponentRotation());

	//총구 화염
	FTransform MuzzleTransform = Weapon->GetSocketTransform(FName(TEXT("MuzzleFlash")));

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
		MuzzleFlash, MuzzleTransform);

	if (bIsFire)
	{
		GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &ABasicPlayer::Shoot, FireTimer);
	}
}

FRotator ABasicPlayer::GetAimOffset() const
{
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	const FRotator AimRotLS = AimDirLS.Rotation();
	return AimRotLS;
}

float ABasicPlayer::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (CurrentHP <= 0)
	{
		return 0;
	}


	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		UE_LOG(LogClass, Warning, TEXT("%f Damage"), DamageAmount);
		FPointDamageEvent* PointDamageEvent = (FPointDamageEvent*)(&DamageEvent);

		if (PointDamageEvent->HitInfo.BoneName.Compare(TEXT("head")) == 0)
		{
			CurrentHP = 0;
		}
		else
		{
			CurrentHP -= DamageAmount;
		}

		UE_LOG(LogClass, Warning, TEXT("%s Damage"), *PointDamageEvent->HitInfo.BoneName.ToString());

		//데미지 타입 처리 방법
		if(PointDamageEvent->DamageTypeClass->IsChildOf(UBasicDamageType::StaticClass()))
		{
			//UBasicDamageType* Type = Cast<UBasicDamageType>(PointDamageEvent->DamageTypeClass);
			UBasicDamageType* Type = NewObject<UBasicDamageType>(PointDamageEvent->DamageTypeClass);
			if(Type)
				UE_LOG(LogClass,Warning,TEXT("Position %d"), Type->PostitionDamage)
		}

	}
	else if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		FRadialDamageEvent* RadialDamageEvent = (FRadialDamageEvent*)(&DamageEvent);
		//RadialDamageEvent->Params.
		UE_LOG(LogClass, Warning, TEXT("Radial Damage %f"), DamageAmount);
	}
	else if (DamageEvent.IsOfType(FDamageEvent::ClassID))
	{

	}

	if (CurrentHP <= 0)
	{
		CurrentHP = 0;
		//죽는 처리
		GetMesh()->SetSimulatePhysics(true);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageAmount;
}

void ABasicPlayer::AddPickupItemList(AMasterItem * Item)
{
	//Null이 아니고 지워지는 리스트에 들은 액터가 아닌 경우
	if (Item && !Item->IsPendingKill())
	{
		CanPickupList.Add(Item);
	}

	//Item이름 나오는 툴팁
	ViewItemToolTip();
}

void ABasicPlayer::RemovePickupItemList(AMasterItem * Item)
{
	if (Item)
	{
		CanPickupList.Remove(Item);
	}

	//Item이름 나오는 툴팁
	ViewItemToolTip();
}

void ABasicPlayer::ViewItemToolTip()
{
	//ABasicPC* PC = Cast<ABasicPC>(GetController());
	ABasicPC* PC = Cast<ABasicPC>(UGameplayStatics::GetPlayerController(GetWorld(),0));

	if (!PC)
	{
		return;
	}

	if (CanPickupList.Num() == 0)
	{
		PC->ShowItemToolTip(false);
		return;
	}

	AMasterItem* CloseItem = CanPickupList[0];

	if (CloseItem)
	{
		PC->ShowItemToolTip(true);
		PC->SetItemName(CloseItem->Data.ItemName);
	}
	else
	{
		PC->ShowItemToolTip(false);
	}
}
