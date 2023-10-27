// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "FPSPlayer.h"

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
void AWeaponBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AFPSPlayer* Player = Cast<AFPSPlayer>(OtherActor);
		if (Player)
		{
			//Add weapon or ammo to player inventory
			Player->AddWeapon(this);
		}
	}
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
	if (!Owner) return;
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
void AWeaponBase::ReadyWeapon() 
{
	WeaponState = EWeaponState::EWS_Idle;
}
void AWeaponBase::HideWeapon(const bool bEnable)
{
	if(bEnable)
	{
		GunMesh->SetVisibility(false);
	}
	else
	{
		GunMesh->SetVisibility(false);
	}
}
void AWeaponBase::SetWeaponOwner(AFPSPlayer* FPSPlayer)
{
	Owner = FPSPlayer;
}
