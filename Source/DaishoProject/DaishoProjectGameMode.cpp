// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DaishoProjectGameMode.h"
#include "DaishoProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UserWidget.h"

ADaishoProjectGameMode::ADaishoProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/DaishoProject/Blueprints/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ADaishoProjectGameMode::BeginPlay()
{
	if(HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(),HUDWidgetClass);
		if(CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
