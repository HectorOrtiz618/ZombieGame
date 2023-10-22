// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPSPlayerAnimInstance.generated.h"

/**
 * 
 */

class FPSPlayer;
UCLASS()
class UEPROJ_API UFPSPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	bool bIsInAir;

	bool bIsUnArmed;
	bool bIsAiming;
	bool bIsReloading;

	float PlayerPitch;
	float PlayerYaw;

	float PlayerMovementX;
	float PlayerMovementY;

protected:
public:
	
};
