

#pragma once
#include "Engine/Texture2D.h"
#include "AIController.h"
#include "BruCharacterData.generated.h"

class UBruCharacterStrength;
class UBruCharacterWeakness;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BRUNESCHARACTERSYSTEM_API UBruCharacterData : public UObject
{
	GENERATED_BODY()
	
public:

	//The character's name to display on HUD.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Information")
	FText CharacterName;

	//The Represented Character's Class
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Technical")
	TSubclassOf<AActor> WorldActorClass;

	//Overrides the AI Controller with this one to easily change personalities with the same actor.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Technical")
	TSubclassOf<AAIController> AIControllerOverride;

	//The starting behavior tree for the AI Controller
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Technical")
	UBehaviorTree* BehaviorTree;

	//The character image that is displayed while they are remotely talking
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Information")
	UTexture2D* CharacterImage;

	//If the character is marked as unique then only one character spawner will spawn the character.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Information")
	bool bIsUnique = true;
		
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Technical")
	TArray<TSubclassOf<UBruCharacterStrength>> CharacterStrengths;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Technical")
	TArray<TSubclassOf<UBruCharacterWeakness>> CharacterWeaknesses;

};
