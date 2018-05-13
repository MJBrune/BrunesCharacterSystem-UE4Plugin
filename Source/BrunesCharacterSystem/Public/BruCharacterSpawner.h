// Copyright Underflow Studios 2017

#pragma once

#include "CoreMinimal.h"
#include "BruCharacterData.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "BruCharacterSpawner.generated.h"

UCLASS()
class BRUNESCHARACTERSYSTEM_API ABruCharacterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ABruCharacterSpawner();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	virtual void BeginPlay() override;


	UFUNCTION()
	virtual void ExtractActorFromCharacterClass();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	virtual AActor* SpawnActorFromCharacterClass();

	UFUNCTION()
	virtual void SetupActor(AActor* NewActor, UBruCharacterData* DefaultCharData);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Spawn Info")
	bool ShouldSpawnInBeginPlay = true;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Spawn Info")
	TSubclassOf<UBruCharacterData> CharacterClass;

	//The region to pass on to the AI.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AITasks")
	FName AITaskRegion;
private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Debug Information")
	UTextRenderComponent* SpawnerOutput;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Debug Information")
	USkeletalMeshComponent* EditorSkelMesh;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Debug Information")
	UStaticMeshComponent* EditorStatMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Debug Information")
	USceneComponent* RootSceneComponent;

	UPROPERTY()
	TSubclassOf<AActor> CachedActorClass;
	
};
