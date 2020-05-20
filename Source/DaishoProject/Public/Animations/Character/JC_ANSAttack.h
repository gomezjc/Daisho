// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "JC_ANSAttack.generated.h"

/**
 * 
 */
UCLASS()
class DAISHOPROJECT_API UJC_ANSAttack : public UAnimNotifyState
{
	GENERATED_BODY()


	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
