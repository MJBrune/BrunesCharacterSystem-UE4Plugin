// Copyright Underflow Studios 2017

#include "BruCharacterManager.h"
#include "BruCharacterDataInterface.h"
#include "GameFramework/Pawn.h"

// Sets default values
ABruCharacterManager::ABruCharacterManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABruCharacterManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABruCharacterManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABruCharacterManager::RegisterCharacter(APawn* CharacterToRegister)
{
	if (!IsValid(CharacterToRegister) || !CharacterToRegister->GetClass()->ImplementsInterface(UBruCharacterDataInterface::StaticClass()))
	{
		return false;
	}
	FBruCachedCharacterInfo NewCharacter;
	NewCharacter.InstancedCharacter = CharacterToRegister;
	NewCharacter.CharacterDataClass = IBruCharacterDataInterface::Execute_GetCharacterData(CharacterToRegister);
	InstancedWorldCharacters.Add(NewCharacter);
	return true;
}

APawn* ABruCharacterManager::FindCharacter(TSubclassOf<UBruCharacterData> SearchCharacterDataClass)
{
	for (FBruCachedCharacterInfo CharacterInfo : InstancedWorldCharacters)
	{
		if (CharacterInfo.CharacterDataClass == SearchCharacterDataClass)
		{
			return CharacterInfo.InstancedCharacter;
		}
	}

	return nullptr;
}

