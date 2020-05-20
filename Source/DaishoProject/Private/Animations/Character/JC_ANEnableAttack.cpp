// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Animations/Character/JC_ANEnableAttack.h"
#include "DaishoProjectCharacter.h"

void UJC_ANEnableAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();

	if (IsValid(CharacterActor))
	{
		ADaishoProjectCharacter* Character = Cast<ADaishoProjectCharacter>(CharacterActor);

		if (IsValid(Character))
		{
			Character->SetActionState(false);
		}
	}
}