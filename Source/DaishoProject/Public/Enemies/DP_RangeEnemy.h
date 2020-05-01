// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/DP_Enemy.h"
#include "DP_RangeEnemy.generated.h"

/**
 * 
 */
UCLASS()
class DAISHOPROJECT_API ADP_RangeEnemy : public ADP_Enemy
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;
	virtual void StartAttack() override;
	virtual void StopAttack() override;
	virtual void OnSeeCharacter(APawn* OtherPawn) override;
public:
	ADP_RangeEnemy();
};
