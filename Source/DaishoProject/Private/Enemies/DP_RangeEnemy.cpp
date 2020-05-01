// Fill out your copyright notice in the Description page of Project Settings.


#include "DP_RangeEnemy.h"


ADP_RangeEnemy::ADP_RangeEnemy()
{
	InitialHealth = 100.0f;
	CurrentHealth = 100.0f;
}

void ADP_RangeEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ADP_RangeEnemy::StartAttack()
{
	
}

void ADP_RangeEnemy::StopAttack()
{
	
}

void ADP_RangeEnemy::OnSeeCharacter(APawn* OtherPawn)
{
	Super::OnSeeCharacter(OtherPawn);
	UE_LOG(LogTemp, Warning, TEXT("Veo al pawn desde el hijo"));
}
