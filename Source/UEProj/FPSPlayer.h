// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Ammo.h"
#include "FPSPlayer.generated.h"


class USkeletalMeshCompoennt;
class UInputMappingContext;
class UInputComponent;
class UInputAction;
struct FInputActionValue;
class UCameraComponent;
class AWeaponBase;
UCLASS()
class UEPROJ_API AFPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//MappingContext
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* FPSContext;
	
	//InputActions
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MovementAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LeanAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* CrouchAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* PrimaryAttackAction;
	TMap<EAmmoType, int32> ReservedAmmo;
	//Player ACtions
	void Move(const FInputActionValue& Value);
	void Reload();
	void LookAround(const FInputActionValue& Value);
	void CrouchPlayer(const FInputActionValue& Value);
	void UnCrouchPlayer(const FInputActionValue& Value);

	void InterpCrouch(float DeltaTime);

	//Helper function to determine if we have enough room to stand up;
	bool StandingHeightBlocked();
	void Attack();
	void UpdateAccuracy(float DeltaTime);

private:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Combat, meta =(AllowPrivateAccess="true"))
	int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	int32 MaxHealth;
	
	bool bCrouched;
	bool bCrouchButtonPressed;

	bool bOverlapped;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Movement,meta=(AllowPrivateAccess="true"))
	float StandingCapsuleHalfHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float CrouchingCapsuleHalfHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float StandingCameraHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float CrouchingCameraHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float CrouchInterpSpeed;

	float MovementInaccuracyFactor;
	float InAirInaccuracyFactor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float MovementInaccuracyRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float JumpingInaccuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float JumpingInaccuracyRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	float WeaponInaccuracy;

	float CurrentCapsuleHalfHeight;
	float CurrentCameraHeight;

	float TargetCapsuleHalfHeight, TargetCameraHeight;

	UPROPERTY(EditAnywhere, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FPArms;
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	
	AWeaponBase* CurrentWeapon;
	AWeaponBase* WeaponSlot1;
	AWeaponBase* WeaponSlot2;
	AWeaponBase* WeaponSlot3;
	AWeaponBase* WeaponSlot4;

	TMap<EAmmoType, int32> ReservedAmmo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE int32 GetHealth()const { return Health; }
	FORCEINLINE int32 GetMaxHealth()const { return MaxHealth; }
	FORCEINLINE void SetAmmoInReserve(const int32 Ammo) {};

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void AddWeapon(AWeaponBase* Weapon, EWeaponType WeaponType);

};
