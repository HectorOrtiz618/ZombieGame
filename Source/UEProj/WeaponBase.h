// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Ammo.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
class AFPSPlayer;
class USoundCue;
class UParticleSystem;
class USkeletalMesh;
UCLASS()
class UEPROJ_API AWeaponBase : public AItemBase
{
	GENERATED_BODY()
private:
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponStats)
	int32 MagazineSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponStats)
	int32 CurrentRoundsInMagazine;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponStats)
	int32 MaxRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WeaponStats)
	USkeletalMesh* GunMesh;
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
	void CockGun();
	FORCEINLINE const float GetMinAccuracy() { return MinAccuracy; };
	FORCEINLINE const float GetMaxAccuracy() { return MaxAccuracy; };
	void SetOwner(AFPSPlayer* FPSPlayer);
};
