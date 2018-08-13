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
		//AddMovementInput(GetActorForwardVector(), value);
		AddMovementInput(UKismetMathLibrary::GetForwardVector(GetControlRotation()), value);
	}
}

void ABasicPlayer::Right(float value)
{
	if (value != 0.0f)
	{
		//AddMovementInput(GetActorRightVector(), value);
		AddMovementInput(UKismetMathLibrary::GetRightVector(GetControlRotation()), value);
	}
}
