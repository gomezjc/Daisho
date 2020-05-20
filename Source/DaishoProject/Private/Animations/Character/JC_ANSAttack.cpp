// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Animations/Character/JC_ANSAttack.h"
#include "DaishoProjectCharacter.h"

void UJC_ANSAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	AActor* CharacterActor = MeshComp->GetOwner();

	if (IsValid(CharacterActor))
	{
		ADaishoProjectCharacter* Character = Cast<ADaishoProjectCharacter>(CharacterActor);

		if (IsValid(Character))
		{
			Character->SetMeleeDetectorCollision(ECollisionEnabled::QueryOnly);
		}
	}
}

void UJC_ANSAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();

	if (IsValid(CharacterActor))
	{
		ADaishoProjectCharacter* Character = Cast<ADaishoProjectCharacter>(CharacterActor);

		if (IsValid(Character))
		{
			Character->SetMeleeDetectorCollision(ECollisionEnabled::NoCollision);
		}
	}
}
