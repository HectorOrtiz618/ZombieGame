// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

class USkeletalMeshComponent;
class UBoxComponent;
class AEnemyController;

UENUM(BlueprintType)
enum class EEnemyState :uint8
{
	EES_Idle UMETA(DisplayName = "Idle"),
	EES_Alert UMETA(DisplayName = "Alert(Suspicious)"),
	EES_Combat UMETA(DisplayName = "Combat(Agressive)"),
	EES_Dead UMETA(DisplayName = "Dead"),

	EES_MAX UMETA(DisplayName = "DEFAULTMAX")
};
UCLASS()
class UEPROJ_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", META =(AllowPrivateAccess = "true"))
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh", META = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* EnemyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat", META = (AllowPrivateAccess = "true"))
	UBoxComponent* HitBox;
	AEnemyController* EnemyController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", META = (AllowPrivateAccess = "true"))
	bool bIsHurt;

	void PlayMontage(FName MontageName);
	void EnableMeleeHitBox();
	void DisableMeleeHitBox();
	void Die();
	void SpawnRagdoll();
private:
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FORCEINLINE float GetHealth()const { return Health; }
	FORCEINLINE bool GetIsHurt()const { return bIsHurt; }

};
