// Copyright Underflow Studios 2017

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BruCharacterWeakness.generated.h"

class UGameplayEffect;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BRUNESCHARACTERSYSTEM_API UBruCharacterWeakness : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character System", meta = (MultiLine = true))
	FString WeaknessTitle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character System", meta = (MultiLine = true))
	FText WeaknessDescription;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character System")
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character System")
	TArray<TSubclassOf<UGameplayAbility>> GrantedAbilities;
};
