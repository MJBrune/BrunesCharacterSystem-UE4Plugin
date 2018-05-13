// Copyright Underflow Studios 2017

#pragma once
#include "BruCharacterSystemTypes.generated.h"

class UBruCharacterData;

USTRUCT(BlueprintType, Blueprintable)
struct FBruCachedCharacterInfo
{
	GENERATED_USTRUCT_BODY()

public:
	//Character Data Class 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic)
	UBruCharacterData* CharacterData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic)
	FName AITaskRegion;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic)
	APawn* InstancedCharacter;
};
