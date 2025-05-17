// Copyright Epic Games, Inc. All Rights Reserved.

#include "TD_MassAIGameMode.h"
#include "TD_MassAICharacter.h"
#include "UObject/ConstructorHelpers.h"

ATD_MassAIGameMode::ATD_MassAIGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
