// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DP_Weapon.generated.h"

UCLASS()
class DAISHOPROJECT_API ADP_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADP_Weapon();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Damage")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Damage")
	TSubclassOf<class UDamageType> DamageType;

	class ACharacter* OwnerCharacter;

public:
	UFUNCTION(BlueprintCallable)
	void SetCharacterOwner(class ACharacter* NewOwner);
};
