// Copyright Underflow Studios 2017

#pragma once

#include "CoreMinimal.h"
#include "BruCharacterData.h"
#include "BruCharacterDataInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBruCharacterDataInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BRUNESCHARACTERSYSTEM_API IBruCharacterDataInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Data")
	TSubclassOf<UBruCharacterData> GetCharacterData();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character Data")
	void GetCharacterMesh(UMeshComponent*& OutMeshComponent);
};
