// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Animations/Character/DP_ANComboDisable.h"

#include "DaishoProjectCharacter.h"

void UDP_ANComboDisable::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();

	if (IsValid(CharacterActor))
	{
		ADaishoProjectCharacter* Character = Cast<ADaishoProjectCharacter>(CharacterActor);

		if (IsValid(Character))
		{
			Character->ResetCombo();
		}
	}
}
