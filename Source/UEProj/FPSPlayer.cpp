// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayer.h"
#include "WeaponBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

// Sets default values
AFPSPlayer::AFPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());

	//Camera is Parent
	FPArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPS Arms"));
	FPArms->SetupAttachment(Camera);

	//ReservedAmmo;
	Health = 100;
	MaxHealth = 100;
	bCrouched = false;
	bCrouchButtonPressed = false;

	MovementInaccuracyFactor = 0;
	InAirInaccuracyFactor = 0;

}

// Called when the game starts or when spawned
void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Set up Camera and capsule size as indicated by the class
	TargetCapsuleHalfHeight = StandingCapsuleHalfHeight;
	TargetCameraHeight = StandingCameraHeight;
	Camera->SetRelativeLocation(FVector(0, 0, TargetCameraHeight));
	GetCapsuleComponent()->SetCapsuleHalfHeight(TargetCapsuleHalfHeight);
	CurrentCameraHeight = StandingCameraHeight;
	CurrentCapsuleHalfHeight = StandingCapsuleHalfHeight;
	bCrouched = false;
	bCrouchButtonPressed = false;

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FPSContext, 0);
		}
	}
	
}

void AFPSPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFPSPlayer::Reload()
{
	//TODO create reload fucntion
}

void AFPSPlayer::LookAround(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFPSPlayer::CrouchPlayer(const FInputActionValue& Value)
{
	bCrouched = true;
	bCrouchButtonPressed = true;
}
void AFPSPlayer::UnCrouchPlayer(const FInputActionValue& Value)
{
	//if(!StandingHeightBlocked())
	//bCrouched = false;
	bCrouchButtonPressed = false;
}
void AFPSPlayer::InterpCrouch(float DeltaTime)
{
	if (bCrouchButtonPressed)
	{
		TargetCapsuleHalfHeight = CrouchingCapsuleHalfHeight;
		TargetCameraHeight = CrouchingCameraHeight;
	}
	else
	{
		if (bCrouched && !bCrouchButtonPressed && !StandingHeightBlocked())
		{
			bCrouched = false;
			TargetCapsuleHalfHeight = StandingCapsuleHalfHeight;
			TargetCameraHeight = StandingCameraHeight;
		}

		
	}
	CurrentCapsuleHalfHeight = FMath::FInterpTo(CurrentCapsuleHalfHeight, TargetCapsuleHalfHeight, DeltaTime, CrouchInterpSpeed);
	CurrentCameraHeight = FMath::FInterpTo(CurrentCameraHeight, TargetCameraHeight, DeltaTime, CrouchInterpSpeed);
	GetCapsuleComponent()->SetCapsuleHalfHeight(CurrentCapsuleHalfHeight);
	FVector CameraLocation = Camera->GetRelativeLocation();
	CameraLocation.Z = CurrentCameraHeight;
	Camera->SetRelativeLocation(CameraLocation);

}
void AFPSPlayer::UpdateAccuracy(float DeltaTime)
{
	if (!CurrentWeapon) return;
	//add inherit accuracy from weapon
	if (this->GetVelocity() == FVector(0))
	{
		//interp to min accuracy
		MovementInaccuracyFactor = FMath::FInterpTo(MovementInaccuracyFactor, CurrentWeapon->GetMinAccuracy(), DeltaTime, MovementInaccuracyRate);
	}
	else
	{
		//interp to min accuracy
		MovementInaccuracyFactor = FMath::FInterpTo(MovementInaccuracyFactor, CurrentWeapon->GetMaxAccuracy(), DeltaTime, MovementInaccuracyRate);
	}
	if (GetMovementComponent()->IsFalling())
	{
		//Interp to Jumping inaccuracy
		InAirInaccuracyFactor = FMath::FInterpTo(MovementInaccuracyFactor, JumpingInaccuracy, DeltaTime, JumpingInaccuracyRate);
	}
	else
	{
		//Interp to zero
		InAirInaccuracyFactor = FMath::FInterpTo(MovementInaccuracyFactor, 0, DeltaTime, JumpingInaccuracyRate);
	}
	//add everything together
	WeaponInaccuracy = MovementInaccuracyFactor + InAirInaccuracyFactor;
}


bool AFPSPlayer::StandingHeightBlocked()
{
	FVector Start = AFPSPlayer::GetActorLocation();
	FVector End = Start;
	End.Z += (CrouchingCapsuleHalfHeight + StandingCapsuleHalfHeight) - CurrentCapsuleHalfHeight;
	FHitResult HitResult;

	DrawDebugLine(GetWorld(), Start, End, FColor::Emerald,false,5.f);
	return GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility);
}

void AFPSPlayer::Attack()
{
	if (CurrentWeapon == nullptr||GetController() == nullptr) return;
	//TODO: set End to CurentWeapon's Max Range, and set 
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + (Camera->GetForwardVector() * 50'000.f);
	FVector BulletEnd = FMath::VRandCone(Start, WeaponInaccuracy/2.f);
	FHitResult WeaponHitResult;

	if (GetWorld()->LineTraceSingleByChannel(WeaponHitResult, Start, BulletEnd, ECollisionChannel::ECC_Visibility))
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Emerald, false, 5.f);
	}
}

// Called every frame
void AFPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AFPSPlayer::InterpCrouch(DeltaTime);
	AFPSPlayer::UpdateAccuracy(DeltaTime);
	
}

// Called to bind functionality to input
void AFPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AFPSPlayer::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSPlayer::LookAround);
		Input->BindAction(PrimaryAttackAction, ETriggerEvent::Triggered, this, &AFPSPlayer::Attack);

		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		Input->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AFPSPlayer::CrouchPlayer);
		Input->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AFPSPlayer::UnCrouchPlayer);
	}

}

