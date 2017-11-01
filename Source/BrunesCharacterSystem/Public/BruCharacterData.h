

#pragma once
#include "Engine/Texture2D.h"
#include "BruCharacterData.generated.h"

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
	
	//The character image that is displayed while they are remotely talking
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Information")
	UTexture2D* CharacterImage;

	//If the character is marked as unique then only one character spawner will spawn the character.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Information")
	bool bIsUnique = true;
};
