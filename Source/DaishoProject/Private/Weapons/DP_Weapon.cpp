// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/DP_Weapon.h"
#include "GameFramework/Character.h"

// Sets default values
ADP_Weapon::ADP_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ADP_Weapon::SetCharacterOwner(ACharacter* NewOwner)
{
	if (IsValid(NewOwner))
	{
		SetOwner(NewOwner);
		OwnerCharacter = NewOwner;
	}
}


