// Copyright Underflow Studios 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BruCharacterSystemTypes.h"
#include "BruCharacterManager.generated.h"

UCLASS()
class BRUNESCHARACTERSYSTEM_API ABruCharacterManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABruCharacterManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Registers a character from a spawner
	UFUNCTION(BlueprintCallable, Category = "Character System")
	bool RegisterCharacter(APawn* CharacterToRegister);

	//Finds and returns the first instanced Character with the class. nullptr if nothing found.
	UFUNCTION(BlueprintCallable, Category = "Character System")
	APawn* FindCharacter(TSubclassOf<UBruCharacterData> SearchCharacterDataClass);

private:

	TArray<FBruCachedCharacterInfo> InstancedWorldCharacters;
	
};
