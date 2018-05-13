// Copyright Underflow Studios 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BruCharacterSystemTypes.h"
#include "BruCharacterManager.generated.h"

class UGameplayEffect;

USTRUCT(BlueprintType, Blueprintable)
struct FBruAITaskInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AITasks")
	FName Region;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AITasks")
	AActor* InterestActor;

	//Higher Priority tasks get actioned first.
	//Todo: Factor in task time to priority.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AITasks")
	uint8 Priority;

	//The amount of time (seconds) it takes to complete the task. -1 is never ending.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AITasks")
	float TaskTime;

	//The gameplay effects to apply once the task is being worked on
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AITasks")
	TArray<TSubclassOf<UGameplayEffect>> StartTaskGameplayEffects;

	//The gameplay effects to apply once the task is being worked on
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AITasks")
	TArray<TSubclassOf<UGameplayEffect>> EndTaskGameplayEffects;

	FBruAITaskInfo()
	{
		Region = "";
		InterestActor = nullptr;
	}

	FBruAITaskInfo(AActor* InInterestActor, FName InRegion)
	{
		Region = InRegion;
		InterestActor = InInterestActor;
	}

	bool operator==(const FBruAITaskInfo& otherActorInfo) const
	{
		return otherActorInfo.InterestActor == this->InterestActor; //Will we ever need two tasks on one actor?
		//Maybe if anything a pointer to the next task to an AI to do to contain a loop
	}

	bool operator>(const FBruAITaskInfo& otherActorInfo) const
	{
		return this->Priority > otherActorInfo.Priority;
	}

	bool operator<(const FBruAITaskInfo& otherActorInfo) const
	{
		return this->Priority < otherActorInfo.Priority;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDBTaskRegistered, FBruAITaskInfo, RegisteredTask);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDBTaskCompleted, FBruAITaskInfo, CompletedTask);

UCLASS()
class BRUNESCHARACTERSYSTEM_API ABruCharacterManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ABruCharacterManager();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//Registers a character from a spawner
	UFUNCTION(BlueprintCallable, Category = "Character System")
	bool RegisterCharacter(APawn* CharacterToRegister, FName AIRegion);

	//Finds and returns the first instanced Character with the class. nullptr if nothing found.
	UFUNCTION(BlueprintCallable, Category = "Character System")
	APawn* FindCharacter(TSubclassOf<UBruCharacterData> SearchCharacterDataClass);

	//Finds and returns the task region tied to this character.
	//Returns 'Character Not Registered' if the character can't be found.
	UFUNCTION(BlueprintCallable, Category = "Character System")
	FName GetCharactersTaskRegion(APawn* WorldCharacter);

	//Registers a task for the AI system
	UFUNCTION(BlueprintCallable, Category = "Character System")
	void RegisterTask(FBruAITaskInfo RegisteringAITask);

	//Registers a point of interest for the wandering AI system
	UFUNCTION(BlueprintCallable, Category = "Character System")
	void CompleteTask(FBruAITaskInfo RegisteringAITask);

	// Returns the full array of points of interest.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character System")
	TArray<FBruAITaskInfo> GetPointsOfInterest(FName Region = TEXT("All"));

	UFUNCTION(BlueprintCallable, Category = "Character System")
	FBruAITaskInfo FindTaskFromInteractingActor(AActor* InteractingActor);

	UFUNCTION(BlueprintCallable, Category = "Character System")
	TArray<FBruAITaskInfo> GetCurrentTasks();

	UPROPERTY(BlueprintAssignable)
	FDBTaskRegistered OnTaskRegistered;

	UPROPERTY(BlueprintAssignable)
	FDBTaskCompleted OnTaskCompleted;

protected:

	//List of interact able actors as points of interest for wandering.
	UPROPERTY()
	TArray<FBruAITaskInfo> CurrentAITasks;

	UPROPERTY()
	TArray<FBruCachedCharacterInfo> InstancedWorldCharacters;
	
};
