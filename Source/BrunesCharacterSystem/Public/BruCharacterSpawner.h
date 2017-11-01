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
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Spawn Info")
	TSubclassOf<UBruCharacterData> CharacterClass;

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
