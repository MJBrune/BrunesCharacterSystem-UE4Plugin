// Copyright Underflow Studios 2017

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BruCharacterStrength.generated.h"

class UGameplayEffect;
class UGameplayAbility;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BRUNESCHARACTERSYSTEM_API UBruCharacterStrength : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character System", meta = (MultiLine = true))
	FString StrengthTitle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character System", meta = (MultiLine = true))
	FText StrengthDescription;
		
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character System")
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffects;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character System")
	TArray<TSubclassOf<UGameplayAbility>> GrantedAbilities;

};
