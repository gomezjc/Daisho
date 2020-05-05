// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Projectiles/DP_Arrow.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "DaishoProjectCharacter.h"

const float ADP_Arrow::ProjectileSpeed = 3000.0f;

// Sets default values
ADP_Arrow::ADP_Arrow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	ProjectileCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionRoot"));

	ProjectileCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	ProjectileCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ProjectileCollision->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	ProjectileCollision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	ProjectileCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	RootComponent = ProjectileCollision;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ProjectileMesh->SetupAttachment(ProjectileCollision);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->InitialSpeed = ADP_Arrow::ProjectileSpeed;
	ProjectileMovementComponent->MaxSpeed = ADP_Arrow::ProjectileSpeed;
	ProjectileMovementComponent->ProjectileGravityScale = 0.2f;
}

// Called when the game starts or when spawned
void ADP_Arrow::BeginPlay()
{
	Super::BeginPlay();	
}

void ADP_Arrow::NotifyActorBeginOverlap(AActor* OtherActor)
{
	ADaishoProjectCharacter* Player = Cast<ADaishoProjectCharacter>(OtherActor);

	if(IsValid(Player))
	{
		UE_LOG(LogTemp, Warning, TEXT("le di al player"));
		Destroy();
	}

}


