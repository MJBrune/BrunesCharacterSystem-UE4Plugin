// Copyright Underflow Studios 2017

#include "BruCharacterSpawner.h"
#include "GameFramework/GameMode.h"
#include "BruCharacterManagerInterface.h"
#include "BruCharacterDataInterface.h"
#include "BruCharacterManager.h"

#define LOCTEXT_NAMESPACE "ABruCharacterSpawner"

// Sets default values
ABruCharacterSpawner::ABruCharacterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>("Root Scene Component");
	SetRootComponent(RootSceneComponent);
	EditorSkelMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Editor Skeleton Mesh");
	EditorStatMesh = CreateDefaultSubobject<UStaticMeshComponent>("Editor Static Mesh");
	EditorSkelMesh->SetHiddenInGame(true, true);

	EditorStatMesh->SetupAttachment(GetRootComponent());
	EditorStatMesh->SetHiddenInGame(true, true);

	EditorSkelMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	EditorStatMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SpawnerOutput = CreateDefaultSubobject<UTextRenderComponent>("Spawner Error Output");
	SpawnerOutput->bHiddenInGame = true;
	SpawnerOutput->SetVisibility(true, true);
	SpawnerOutput->SetupAttachment(GetRootComponent());
	SpawnerOutput->SetVerticalAlignment(EVRTA_TextCenter);
	SpawnerOutput->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 100.f), FRotator(0.f, 00.f, 0.f));
}

void ABruCharacterSpawner::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (IsValid(CharacterClass))
	{
		UBruCharacterData* DefaultCharData = Cast<UBruCharacterData>(CharacterClass->GetDefaultObject());
		const bool IsObjectsValid = IsValid(DefaultCharData) && IsValid(DefaultCharData->WorldActorClass);
		if (IsObjectsValid && DefaultCharData->WorldActorClass->ImplementsInterface(UBruCharacterDataInterface::StaticClass()))
		{
			CachedActorClass = DefaultCharData->WorldActorClass;
			UMeshComponent* TempMeshComponent = nullptr;
			IBruCharacterDataInterface::Execute_GetCharacterMesh(CachedActorClass->GetDefaultObject(), TempMeshComponent);
			USkeletalMeshComponent* TempSkelMesh = Cast<USkeletalMeshComponent>(TempMeshComponent);

			if (IsValid(TempSkelMesh))
			{
				EditorSkelMesh->SetSkeletalMesh(TempSkelMesh->SkeletalMesh);
				EditorSkelMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
				EditorSkelMesh->AnimClass = TempSkelMesh->AnimClass;
				EditorSkelMesh->SetRelativeTransform(TempSkelMesh->GetRelativeTransform());
			}
			else
			{
				EditorSkelMesh->SetSkeletalMesh(nullptr);
			}
			
			 IBruCharacterDataInterface::Execute_GetCharacterMesh(CachedActorClass->GetDefaultObject(), TempMeshComponent);
			UStaticMeshComponent* TempStatMesh = Cast<UStaticMeshComponent>(TempMeshComponent);

			if (IsValid(TempStatMesh))
			{
				EditorStatMesh->SetStaticMesh(TempStatMesh->GetStaticMesh());
				EditorStatMesh->SetRelativeTransform(TempStatMesh->GetRelativeTransform());
			}
			else
			{
				EditorStatMesh->SetStaticMesh(nullptr);
			}

			SpawnerOutput->SetText(DefaultCharData->CharacterName);
		}
		else
		{
			EditorSkelMesh->SetSkeletalMesh(nullptr);
			EditorStatMesh->SetStaticMesh(nullptr);
			SpawnerOutput->SetText(LOCTEXT("Debug", "Actor Class in the Character Data Class DOES NOT IMPLEMENT Character Data Class."));
		}
	}
	else
	{
		EditorSkelMesh->SetSkeletalMesh(nullptr);
		EditorStatMesh->SetStaticMesh(nullptr);
		SpawnerOutput->SetText(LOCTEXT("Debug","CharacterClass Not Set!"));
	}
}

// Called every frame
void ABruCharacterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABruCharacterSpawner::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(CachedActorClass) && Role >= ROLE_Authority)
	{
		FActorSpawnParameters Params;

		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Params.bDeferConstruction = true; // We defer construction so that we set ParentComponent prior to component registration so they appear selected
		Params.bAllowDuringConstructionScript = true;
		Params.OverrideLevel = GetLevel();
		Params.ObjectFlags |= (RF_TextExportTransient | RF_NonPIEDuplicateTransient);

		if (!HasAllFlags(RF_Transactional))
		{
			Params.ObjectFlags &= ~RF_Transactional;
		}

		FVector Location = GetActorLocation();
		FRotator Rotation = GetActorRotation();
		
		UWorld* World = GetWorld();

		AActor* NewActor = World->SpawnActor(CachedActorClass, &Location, &Rotation, Params);
		if (NewActor)
		{
			APawn* NewPawn = Cast<APawn>(NewActor);
			if (NewPawn)
			{
				NewPawn->SpawnDefaultController();
			}
			NewActor->FinishSpawning(GetActorTransform());

			AGameModeBase* GameMode = World->GetAuthGameMode();

			if (GameMode->GetClass()->ImplementsInterface(UBruCharacterManagerInterface::StaticClass()))
			{
				ABruCharacterManager* CharacterManager = IBruCharacterManagerInterface::Execute_GetCharacterManager(GameMode);
				if (IsValid(CharacterManager))
				{
					CharacterManager->RegisterCharacter(NewPawn);
				}
			}
		}
	}

	Destroy(); //Spawned it, did my thing, gunna go die nao. RIP
}

