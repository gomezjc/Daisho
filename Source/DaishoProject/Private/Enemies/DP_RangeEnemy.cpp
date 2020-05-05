// Fill out your copyright notice in the Description page of Project Settings.


#include "DP_RangeEnemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Public/Weapons/Projectiles/DP_Arrow.h"

ADP_RangeEnemy::ADP_RangeEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	InitialHealth = 100.0f;
	CurrentHealth = 100.0f;
	ProjectileSocketName = "SKC_Arrow";
}

void ADP_RangeEnemy::BeginPlay()
{
	Super::BeginPlay();
	CurrentState = EEnemyState::EPatrol;
}

void ADP_RangeEnemy::StartAttack()
{
	if (IsValid(ProjectileClass) && IsValid(TargetPlayer))
	{
		USkeletalMeshComponent* CharacterMeshComponent = GetMesh();
		FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(ProjectileSocketName);
		FVector TargetPredict = TargetPlayer->GetVelocity() * (GetDistanceTo(TargetPlayer) / ADP_Arrow::ProjectileSpeed);
		FRotator Target = UKismetMathLibrary::FindLookAtRotation(MuzzleSocketLocation,(TargetPlayer->GetActorLocation() + TargetPredict));
		ADP_Arrow* CurrentProjectile = GetWorld()->SpawnActor<ADP_Arrow>(ProjectileClass, MuzzleSocketLocation, Target);
	}
}

void ADP_RangeEnemy::StopAttack()
{
	
}

void ADP_RangeEnemy::Tick(float DeltaSeconds)
{
	if(bIsChasingPlayer)
	{
		FRotator LookAtRotation = FRotator(0,UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPlayer->GetActorLocation()).Yaw,0);
		SetActorRotation(LookAtRotation);
	}
}

void ADP_RangeEnemy::OnSeeCharacter(APawn* OtherPawn)
{
	Super::OnSeeCharacter(OtherPawn);
	bCanAttack = true;
}
