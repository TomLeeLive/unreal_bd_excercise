// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicPlayer.generated.h"

UCLASS()
class UNREAL_CPP_BD_API ABasicPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Pitch(float value);

	void Yaw(float value);

	void Forward(float value);

	void Right(float value);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UWeaponComponent* Weapon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsIronSight = false;
	
	void TryCrouch();

	void TryIronsight();

	void StartFire();
	void StopFire();
	void Shoot();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float JogSpeed = 360.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float WalkSpeed = 150.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CrouchSpeed = 150.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsFire = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FireTimer = 0.2f;

	FTimerHandle ShootTimerHandle;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UParticleSystem* HitEffect;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class USoundBase* ShootSound;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UMaterialInstance* BulletDecal;

};