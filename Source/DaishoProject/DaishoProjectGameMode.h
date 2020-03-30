// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DaishoProjectGameMode.generated.h"

UCLASS(minimalapi)
class ADaishoProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADaishoProjectGameMode();

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="HUD", Meta=(BlueprintProtected="true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;
};



