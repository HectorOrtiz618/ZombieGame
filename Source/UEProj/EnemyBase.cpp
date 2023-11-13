// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Enemy Mesh"));
	EnemyMesh->SetupAttachment(GetRootComponent());

	LeftArmHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Left Arm Hitbox"));
	LeftArmHitBox->SetupAttachment(GetMesh(),FName("LeftHandSocket"));

	RightArmHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Right Arm Hitbox"));
	RightArmHitBox->SetupAttachment(GetMesh(), FName("RightHandSocket"));


}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	Health = 50;
	EnemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyMesh"));
	
}

void AEnemyBase::EnableMeleeHitBox(UBoxComponent* HitBoxToEnable)
{
}

void AEnemyBase::DisableMeleeHitBox(UBoxComponent* HitBoxToDisable)
{
}

void AEnemyBase::Die()
{
}

void AEnemyBase::SpawnRagdoll()
{
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

