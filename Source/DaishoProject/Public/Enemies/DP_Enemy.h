// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DP_Enemy.generated.h"

UCLASS()
class DAISHOPROJECT_API ADP_Enemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADP_Enemy();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	float InitialHealth;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon")
	TSubclassOf<class ADP_Weapon> InitialWeaponClass;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	class ADP_Weapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="IA")
	class UPawnSensingComponent* PawnSensingComponent;
	
private:
	void CreateInitialWeapon();
	
protected:
	virtual void BeginPlay() override;
	virtual void StartAttack() {};
	virtual void StopAttack() {};

	UFUNCTION()
	virtual void OnSeeCharacter(APawn* OtherPawn);
};
