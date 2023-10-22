// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

AWeaponBase::AWeaponBase()
{
	Owner = nullptr;
	MinAccuracy = 0;
	MaxAccuracy = 0;
	MaxRange = 0;
	TracesPerShot = 1;
	bMagInserted = true;
	bReloadOneBulletAtATime = false;
	WeaponState = EWeaponState::EWS_Idle;
}
void AWeaponBase::FireGun()
{
	if (Owner == nullptr ||  CurrentRoundsInMagazine == 0||WeaponState != EWeaponState::EWS_Idle) return;
	CurrentRoundsInMagazine--;
	if (CurrentRoundsInMagazine <= 0)
	{
		WeaponState = EWeaponState::EWS_Empty;
	}
	
}
void AWeaponBase::UnloadMag()
{
	//TODO: Give remainging rounds to owner and delet rounds in mag
	CurrentRoundsInMagazine = 0;
}
void AWeaponBase::StartReload()
{
	if (CurrentRoundsInMagazine >= MagazineSize || !Owner) return;
	WeaponState = EWeaponState::EWS_Reloading;
}
void AWeaponBase::InsertMag()
{
	if (bReloadOneBulletAtATime)
	{
		if (CurrentRoundsInMagazine < MagazineSize)
		{
			CurrentRoundsInMagazine++;
		}
	}
	else
	{
		if (CurrentRoundsInMagazine < MagazineSize && (CurrentRoundsInMagazine != 0))
		{
			CurrentRoundsInMagazine = MagazineSize + 1;
		}
		else if(CurrentRoundsInMagazine == 0)
		{
			CurrentRoundsInMagazine = MagazineSize;
		}
		else
		{
			//do nothing lmao
		}
	}
}
void AWeaponBase::CockGun() 
{
	WeaponState = EWeaponState::EWS_Idle;
}
void AWeaponBase::SetOwner(AFPSPlayer* FPSPlayer)
{
	Owner = FPSPlayer;
}
