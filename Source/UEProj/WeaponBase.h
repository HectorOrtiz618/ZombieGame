// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Ammo.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
class USphereComponent;
class AFPSPlayer;
class USoundCue;
class UParticleSystem;
class USkeletalMeshComponent;
UCLASS()
class UEPROJ_API AWeaponBase : public AItemBase
{
	GENERATED_BODY()
private:
protected:
	USphereComponent* PickupSphere;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponStats)
	int32 MagazineSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponStats)
	int32 CurrentRoundsInMagazine;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponStats)
	int32 MaxRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponStats)
	USkeletalMeshComponent* GunMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponStats)
	EWeaponType WeaponType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponStats)
	EAmmoType AmmoType;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponStats)
	float TimeBetweenShots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponStats)

	EWeaponState WeaponState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponStats)
	float DamagePerShot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponStats)
	float MinAccuracy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponStats)
	float MaxAccuracy;
	bool bAutomatic;
	bool bReloadOneBulletAtATime;
	bool bMagInserted;
	int32 TracesPerShot;
	UParticleSystem* MuzzleSmoke;
	UParticleSystem* EjectionPortSmoke;
	USoundCue* WeaponSound;
	USoundCue* MagUnloadSound;
	USoundCue* MagInsertSound;
	USoundCue* WeaponCockSound;
	AFPSPlayer* Owner;
public:
	AWeaponBase();
	void FireGun();
	void StartReload();
	void UnloadMag();
	void InsertMag();
	void ReadyWeapon();
	FORCEINLINE const float GetMinAccuracy() { return MinAccuracy; };
	FORCEINLINE const float GetMaxAccuracy() { return MaxAccuracy; };
	FORCEINLINE const int32 GetCurrentRoundsInMag() { return CurrentRoundsInMagazine; };
	FORCEINLINE const EAmmoType GetAmmoType() { return AmmoType; };
	FORCEINLINE const EWeaponType GetWeaponType() { return WeaponType; };
	void HideWeapon(const bool bEnable);
	void SetWeaponOwner(AFPSPlayer* FPSPlayer);
};
