// Copyright Underflow Studios 2017

#include "BruCharacterSpawner.h"
#include "GameFramework/GameMode.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BruCharacterManagerInterface.h"
#include "BruCharacterDataInterface.h"
#include "BruCharacterManager.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "BruCharacterStrength.h"
#include "BruCharacterWeakness.h"

#define LOCTEXT_NAMESPACE "ABruCharacterSpawner"

ABruCharacterSpawner::ABruCharacterSpawner()
{
	PrimaryActorTick.bCanEverTick = false; // TICK IS OFF

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
	SpawnerOutput->SetHorizontalAlignment(EHTA_Center);
	SpawnerOutput->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 100.f), FRotator(0.f, 00.f, 0.f));
}

void ABruCharacterSpawner::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ExtractActorFromCharacterClass();
}

void ABruCharacterSpawner::BeginPlay()
{
	Super::BeginPlay();
	if (ShouldSpawnInBeginPlay)
	{
		SpawnActorFromCharacterClass();
		Destroy(); //Spawned it, did my thing, gunna go die nao. RIP
	}
}

void ABruCharacterSpawner::ExtractActorFromCharacterClass()
{
	if (IsValid(CharacterClass))
	{
		const UBruCharacterData* DefaultCharData = Cast<UBruCharacterData>(CharacterClass->GetDefaultObject());
		const bool IsObjectsValid = IsValid(DefaultCharData) && IsValid(DefaultCharData->WorldActorClass);
		if (IsObjectsValid && DefaultCharData->WorldActorClass->ImplementsInterface(UBruCharacterDataInterface::StaticClass()))
		{
			CachedActorClass = DefaultCharData->WorldActorClass;
			UMeshComponent* TempMeshComponent = nullptr;
			IBruCharacterDataInterface::Execute_GetCharacterMesh(CachedActorClass->GetDefaultObject(), TempMeshComponent);
			const USkeletalMeshComponent* TempSkelMesh = Cast<USkeletalMeshComponent>(TempMeshComponent);

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
			const UStaticMeshComponent* TempStatMesh = Cast<UStaticMeshComponent>(TempMeshComponent);

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
		SpawnerOutput->SetText(LOCTEXT("Debug", "CharacterClass Not Set!"));
	}
}

AActor* ABruCharacterSpawner::SpawnActorFromCharacterClass()
{
	ExtractActorFromCharacterClass();
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

		const FVector Location = GetActorLocation();
		const FRotator Rotation = GetActorRotation();

		UWorld* World = GetWorld();

		AActor* NewActor = World->SpawnActor(CachedActorClass, &Location, &Rotation, Params);
		APawn* NewPawn = Cast<APawn>(NewActor);

		if (NewPawn)
		{
			IBruCharacterDataInterface::Execute_SetCharacterData(NewActor, CharacterClass);

			AGameModeBase* GameMode = World->GetAuthGameMode();
			ABruCharacterManager* CharacterManager = nullptr;

			UBruCharacterData* DefaultCharData = Cast<UBruCharacterData>(CharacterClass->GetDefaultObject());

			if (IsValid(DefaultCharData->AIControllerOverride))
			{
				NewPawn->AIControllerClass = DefaultCharData->AIControllerOverride;
			}

			if (GameMode && GameMode->GetClass()->ImplementsInterface(UBruCharacterManagerInterface::StaticClass()))
			{
				CharacterManager = IBruCharacterManagerInterface::Execute_GetCharacterManager(GameMode);

				if (DefaultCharData->bIsUnique)
				{
					if (IsValid(CharacterManager) && IsValid(CharacterManager->FindCharacter(CharacterClass)))
					{
						//Should be unique. Kill the chosen one!
						NewActor->Destroy();
						return nullptr;
					}
				}
			}

			SetupActor(NewActor, DefaultCharData);

			NewPawn->SpawnDefaultController();

			NewActor->FinishSpawning(GetActorTransform());

			if (IsValid(CharacterManager))
			{
				CharacterManager->RegisterCharacter(NewPawn, AITaskRegion);
			}

			return NewPawn;
		}
	}

	return nullptr;

}

void ABruCharacterSpawner::SetupActor(AActor* NewActor, UBruCharacterData* DefaultCharData)
{
	IAbilitySystemInterface* AbilityInterface = Cast<IAbilitySystemInterface>(NewActor);
	if (AbilityInterface)
	{
		for (TSubclassOf<UBruCharacterStrength> StrengthClass : DefaultCharData->CharacterStrengths)
		{
			UBruCharacterStrength* BruStrength = StrengthClass->GetDefaultObject<UBruCharacterStrength>();

			for (TSubclassOf<UGameplayEffect> GameplayEffectsClass : BruStrength->GameplayEffects)
			{

				UAbilitySystemComponent* AbilitySystemComponent = AbilityInterface->GetAbilitySystemComponent();
				AbilitySystemComponent->ApplyGameplayEffectToSelf(GameplayEffectsClass->GetDefaultObject<UGameplayEffect>(), 1.f, FGameplayEffectContextHandle());
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE