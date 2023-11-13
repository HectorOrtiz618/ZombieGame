// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * Base Enemy AI controller, will determine enemy logic
 */
UCLASS()
class UEPROJ_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
protected:
	UBehaviorTree* BehaviorTree;
private:
public:
	
};
