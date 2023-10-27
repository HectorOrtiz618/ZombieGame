#pragma once
//Used to be only for the ammo type enum, but now used for any shared enums for classes
UENUM(BlueprintType)
enum class EAmmoType : uint8
{
	EAT_9MM		UMETA(DisplayName = "9mm Ammo"),
	EAT_SHELLS		UMETA(DisplayName = "Shotgun Ammo"),
	EAT_AR		UMETA(DisplayName = "Assault Rifle Ammo"),

	EAT_MAX		UMETA(DisplayName = "Default MAX"),

};
UENUM(BlueprintType)
enum class EWeaponType :uint8
{
	EWT_Knife UMETA(DisplayName = "Knife"),
	EWT_Pistol UMETA(DisplayName = "Pistol"),
	EWT_PumpShotgun UMETA(DisplayName = "PumpShotgun"),
	EWT_Rifle UMETA(DisplayName = "Rifle"),

	EWT_MAX UMETA(DisplayName = "DEFAULTMAX")
};
UENUM(BlueprintType)
enum class EWeaponState :uint8
{
	EWS_Idle UMETA(DisplayName = "Idle"),
	EWS_Drawing UMETA(DisplayName = "Draw Weapon"),
	EWS_Empty UMETA(DisplayName = "Empty"),
	EWS_CycleRound UMETA(DisplayName = "Cycle Round"),
	EWS_Reloading UMETA(DisplayName = "Reloading"),

	EES_MAX UMETA(DisplayName = "DEFAULTMAX")
};
UENUM(BlueprintType)
enum class EPlayerState :uint8
{
	EPS_Idle UMETA(DisplayName = "Idle"),
	EPS_Reloading UMETA(DisplayName = "Reloading"),
	EPS_Dead	UMETA(DispplayName = "Dead"),

	EES_MAX UMETA(DisplayName = "DEFAULTMAX")
};