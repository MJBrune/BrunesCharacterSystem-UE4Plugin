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
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Brune's Character System")
	void SetCharacterData(TSubclassOf<UBruCharacterData> InCharacterData);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Brune's Character System")
	UBruCharacterData* GetCharacterData();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Brune's Character System")
	void GetCharacterMesh(UMeshComponent*& OutMeshComponent);
};
