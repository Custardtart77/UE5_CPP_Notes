// Copyright Epic Games, Inc. All Rights Reserved.

#include "BidDemoGameMode.h"
#include "BidDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABidDemoGameMode::ABidDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
