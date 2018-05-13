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

bool ABruCharacterManager::RegisterCharacter(APawn* CharacterToRegister, FName AIRegion)
{
	if (!IsValid(CharacterToRegister) || !CharacterToRegister->GetClass()->ImplementsInterface(UBruCharacterDataInterface::StaticClass()))
	{
		return false;
	}
	FBruCachedCharacterInfo NewCharacter;
	NewCharacter.InstancedCharacter = CharacterToRegister;
	NewCharacter.CharacterData = IBruCharacterDataInterface::Execute_GetCharacterData(CharacterToRegister);
	NewCharacter.AITaskRegion = AIRegion;
	InstancedWorldCharacters.Add(NewCharacter);
	return true;
}

APawn* ABruCharacterManager::FindCharacter(TSubclassOf<UBruCharacterData> SearchCharacterDataClass)
{
	for (FBruCachedCharacterInfo CharacterInfo : InstancedWorldCharacters)
	{
		if (CharacterInfo.CharacterData->GetClass() == SearchCharacterDataClass)
		{
			return CharacterInfo.InstancedCharacter;
		}
	}

	return nullptr;
}

FName ABruCharacterManager::GetCharactersTaskRegion(APawn* WorldCharacter)
{
	for (FBruCachedCharacterInfo CharacterInfo : InstancedWorldCharacters)
	{
		if (CharacterInfo.InstancedCharacter == WorldCharacter)
		{
			return CharacterInfo.AITaskRegion;
		}
	}
	return "Character Not Registered";
}

void ABruCharacterManager::RegisterTask(FBruAITaskInfo RegisteringAITask)
{
	if (IsValid(RegisteringAITask.InterestActor))
	{
		CurrentAITasks.AddUnique(RegisteringAITask);
		OnTaskRegistered.Broadcast(RegisteringAITask);
	}
}

void ABruCharacterManager::CompleteTask(FBruAITaskInfo RegisteringAITask)
{
	if (IsValid(RegisteringAITask.InterestActor))
	{
		CurrentAITasks.Remove(RegisteringAITask);
		OnTaskCompleted.Broadcast(RegisteringAITask);
	}
}

TArray<FBruAITaskInfo> ABruCharacterManager::GetPointsOfInterest(FName Region)
{
	TArray<FBruAITaskInfo> AllInterestActors;

	for (FBruAITaskInfo InterestedActorInfo : GetCurrentTasks())
	{
		if (Region == InterestedActorInfo.Region || Region == TEXT("All"))
		{
			AllInterestActors.AddUnique(InterestedActorInfo);
		}
	}

	return AllInterestActors;
}

FBruAITaskInfo ABruCharacterManager::FindTaskFromInteractingActor(AActor* InteractingActor)
{
	for (FBruAITaskInfo InterestedActorInfo : CurrentAITasks)
	{
		if (InterestedActorInfo.InterestActor == InteractingActor)
		{
			return InterestedActorInfo;
		}
	}

	return FBruAITaskInfo();
}

TArray<FBruAITaskInfo> ABruCharacterManager::GetCurrentTasks()
{
	CurrentAITasks.Sort([](const FBruAITaskInfo& A, const FBruAITaskInfo& B) { return A > B; });
	return CurrentAITasks;
}
