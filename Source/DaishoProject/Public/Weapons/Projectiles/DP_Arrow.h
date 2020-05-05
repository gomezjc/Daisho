// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DP_Arrow.generated.h"

UCLASS()
class DAISHOPROJECT_API ADP_Arrow : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* ProjectileCollision;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UProjectileMovementComponent* ProjectileMovementComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	ADP_Arrow();

	static const float ProjectileSpeed;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
