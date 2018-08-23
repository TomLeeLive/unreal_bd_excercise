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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
	bool bIsIronSight = false;
	
	void TryCrouch();

	void TryIronsight();

	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_TryIronsight();
	bool C2S_TryIronsight_Validate();
	void C2S_TryIronsight_Implementation();

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
		class UParticleSystem* BloodEffect;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class USoundBase* ShootSound;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UMaterialInstance* BulletDecal;

	FRotator GetAimOffset() const;

	FVector NormalSpringArmPosition;
	FVector CrouchSpringArmPosition;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentHP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxHP = 100.0f;

	TArray<class AMasterItem*> CanPickupList;

	UFUNCTION(BlueprintCallable)
	void AddPickupItemList(class AMasterItem* Item);

	UFUNCTION(BlueprintCallable)
	void RemovePickupItemList(class AMasterItem* Item);
	void ViewItemToolTip();

	void Pickup();

	void Inventory();
	AMasterItem * GetClosestItem();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
};
