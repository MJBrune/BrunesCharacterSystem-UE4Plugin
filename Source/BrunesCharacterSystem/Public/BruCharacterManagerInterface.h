// Copyright Underflow Studios 2017

#pragma once

#include "CoreMinimal.h"
#include "BruCharacterManagerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBruCharacterManagerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BRUNESCHARACTERSYSTEM_API IBruCharacterManagerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//returns the character manager so we can find on the game mode.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Brune's Character System")
	ABruCharacterManager* GetCharacterManager();
};
