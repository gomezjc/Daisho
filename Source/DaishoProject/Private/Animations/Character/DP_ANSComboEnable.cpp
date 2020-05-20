// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Animations/Character/DP_ANSComboEnable.h"
#include "DaishoProjectCharacter.h"

void UDP_ANSComboEnable::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	AActor* CharacterActor = MeshComp->GetOwner();

	if (IsValid(CharacterActor))
	{
		ADaishoProjectCharacter* Character = Cast<ADaishoProjectCharacter>(CharacterActor);

		if (IsValid(Character))
		{
			UE_LOG(LogTemp, Warning, TEXT("Activo combo"));
			Character->SetComboEnabled(true);
		}
	}
}

void UDP_ANSComboEnable::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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