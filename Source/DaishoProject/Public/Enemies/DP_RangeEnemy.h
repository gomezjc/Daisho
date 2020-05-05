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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weaoib")
	TSubclassOf<class ADP_Arrow> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName ProjectileSocketName;
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void StartAttack() override;

	virtual void StopAttack() override;

	virtual void OnSeeCharacter(APawn* OtherPawn) override;
	
public:
	ADP_RangeEnemy();
};
