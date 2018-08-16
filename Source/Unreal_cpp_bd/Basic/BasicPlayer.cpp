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

// Sets default values
ABasicPlayer::ABasicPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//�޽� ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Male(TEXT("SkeletalMesh'/Game/Male_Grunt/Mesh/male_grunt.male_grunt'"));

	if (SK_Male.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Male.Object);
	}

	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));
	GetMesh()->SetRelativeLocation(FVector(0, 0,-88.0f));

	//�ִϸ��̼� ���� ����Ʈ ����
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


}

// Called when the game starts or when spawned
void ABasicPlayer::BeginPlay()
{
	Super::BeginPlay();
	
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
		//ī�޶��� Yaw ���и� �̿��ؼ� ���� ���� �����, ȭ�鿡�� ���� ����
		FRotator Rotation = GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);
		AddMovementInput(UKismetMathLibrary::GetForwardVector(YawRotation), value);

		//������ �չ���
		//AddMovementInput(GetActorForwardVector(), value);

		//����ȸ���� �չ���, ī�޶� ���� ����
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
	// �����߿��� �ȴ� �ӵ�
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

	//3���� ������ ī�޶� ��ġ�� ȸ��
	FVector CameraLocation;
	FRotator CameraRotation;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerViewPoint(CameraLocation, CameraRotation);

	//ȭ�� ��ǥ�� ũ�� ��������
	int SizeX;
	int SizeY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(SizeX, SizeY);

	//ȭ�� ��� 2D-> 3D ��ȯ (ī�޶� ����, �÷��� ��Ʈ�ѷ�)
	FVector CrosshairWorldLocation;
	FVector CrosshairWorldDirection;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectScreenPositionToWorld(SizeX / 2, SizeY / 2, CrosshairWorldLocation, CrosshairWorldDirection);

	FVector TraceStart = CameraLocation;
	FVector TraceEnd = CameraLocation + (CrosshairWorldDirection * 80000.0f);

	//���� ������ ���� ���� ����
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	TArray<AActor*> IgnoreActors;
	FHitResult OutHit;

	ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectType.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	IgnoreActors.Add(this);

	//���� ����
	bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(),
		TraceStart,		//Ʈ���̽� ������
		TraceEnd,		//Ʈ���̽� ����
		ObjectType,		//Ʈ���̽� ���� �� ������Ʈ Ÿ�Ե�
		false,			//���� �ø��� ��� ����
		IgnoreActors,	// ���� ���� ����Ʈ
		EDrawDebugTrace::ForDuration, //����� ���� �׸��� ����
		OutHit,			//�浹 ����
		true,			//�ڱ� �ڽ� ����
		FLinearColor::Red,	//����� ���� ����.
		FLinearColor::Blue, //�浹 ���� ����� �ڽ� ����.
		5.0					//����� ���� �׸��� �ð�.
	);


	if (Result)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
			HitEffect, OutHit.ImpactPoint, FRotator::ZeroRotator);

		UGameplayStatics::SpawnDecalAtLocation(GetWorld(),
			BulletDecal,
			FVector(5.0f, 5.0f, 5.0f),
			OutHit.ImpactPoint,
			FRotator(-90, 0, 0), 3.0f);
	}

	//�ѼҸ�
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(),
		ShootSound, Weapon->GetComponentLocation(),
		Weapon->GetComponentRotation());

	//�ѱ� ȭ��
	FTransform MuzzleTransform = Weapon->GetSocketTransform(FName(TEXT("MuzzleFlash")));

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
		MuzzleFlash, MuzzleTransform);

	if (bIsFire)
	{
		GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &ABasicPlayer::Shoot, FireTimer);
	}
}