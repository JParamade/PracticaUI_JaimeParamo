// Copyright Epic Games, Inc. All Rights Reserved.

#include "JPB_PAVJ_UIGameMode.h"
#include "JPB_PAVJ_UICharacter.h"
#include "UObject/ConstructorHelpers.h"

AJPB_PAVJ_UIGameMode::AJPB_PAVJ_UIGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
