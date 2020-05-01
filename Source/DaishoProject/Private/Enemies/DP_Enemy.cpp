// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Enemies/DP_Enemy.h"
#include "Public/AI/DP_AIController.h"
#include "Public/Weapons/DP_Weapon.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ADP_Enemy::ADP_Enemy()
{
	AIControllerClass = ADP_AIController::StaticClass();
	CreateInitialWeapon();
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensingComponent->SetPeripheralVisionAngle(45.0f);
}

void ADP_Enemy::BeginPlay()
{
	Super::BeginPlay();
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ADP_Enemy::OnSeeCharacter);
	UE_LOG(LogTemp, Warning, TEXT("Inicio2"));
}

void ADP_Enemy::CreateInitialWeapon()
{

	if (IsValid(InitialWeaponClass))
	{
		CurrentWeapon = GetWorld()->SpawnActor<ADP_Weapon>(InitialWeaponClass, GetActorLocation(), GetActorRotation());
		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetCharacterOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
}

void ADP_Enemy::OnSeeCharacter(APawn* OtherPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Veo al pawn"));
}
