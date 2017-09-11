// Copyright 2016-2017 Hunter Delattre

#include "Wizz.h"
#include "DungeonMinimap.h"


// Sets default values
ADungeonMinimap::ADungeonMinimap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SetMobility(EComponentMobility::Movable);

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SpawnRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnRoot"));
    SpawnRoot->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

ADungeonMinimap::~ADungeonMinimap()
{
    for (DungeonMinimapIndicatorMarker* Indicator : Indicators) {
        delete Indicator;
    }
}

// Called when the game starts or when spawned
void ADungeonMinimap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADungeonMinimap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    for (DungeonMinimapIndicatorMarker* IndicatorMarker : Indicators) {
        UpdateIndicator(IndicatorMarker);
    }
}

void ADungeonMinimap::Setup(ADungeonGenerator* Dungeon, UDungeonTheme* MinimapTheme, const FVector& Bounds)
{
    MappedDungeon = Dungeon;
    Theme = MinimapTheme;
    DisplayBounds = Bounds;

    CreateArchitecture();
}

void ADungeonMinimap::CreateArchitecture()
{
    if (MappedDungeon == nullptr) {
        return;
    }
    DungeonSector* MappedSector = MappedDungeon->GetCurrentSector();

    minimapCellSize = FMath::Min(DisplayBounds.X / MappedSector->lengthY, DisplayBounds.Y / MappedSector->lengthX);

    for (DungeonStaticMeshMarker* Marker : DungeonMarkerProducer::CreateSectorArchitectureMarkers(*MappedSector)) {
        Marker->SetTheme(Theme);
        ConsumeMarkerForMesh(Marker);
    }

    FVector Adjustment = FVector(1.0f, 1.0f, 0.f) * (minimapCellSize / 2);

    SpawnRoot->SetRelativeLocation(Adjustment);
}

AActor* ADungeonMinimap::CreateIndicatorForActor(AActor* IndicatedActor)
{
    DungeonMinimapIndicatorMarker* IndicatorMarker = new DungeonMinimapIndicatorMarker(IndicatedActor, MappedDungeon->cellSize, minimapCellSize);
    IndicatorMarker->SetTheme(Theme);

    UpdateIndicator(IndicatorMarker);

    Indicators.Add(IndicatorMarker);

    return IndicatorMarker->SpawnedActor;
}

AActor* ADungeonMinimap::CreateRotationalIndicatorForActor(AActor* IndicatedActor, USceneComponent* RotationComponent)
{
    if (RotationComponent == nullptr) {
        RotationComponent = IndicatedActor->GetRootComponent();
    }

    DungeonMinimapIndicatorMarker* IndicatorMarker = new DungeonPlayerIndicatorMarker(IndicatedActor, RotationComponent, MappedDungeon->cellSize, minimapCellSize);
    IndicatorMarker->SetTheme(Theme);

    UpdateIndicator(IndicatorMarker);

    Indicators.Add(IndicatorMarker);

    return IndicatorMarker->SpawnedActor;
}

void ADungeonMinimap::UpdateIndicator(DungeonMinimapIndicatorMarker* IndicatorMarker)
{
    if (IndicatorMarker->IndicatedActor != nullptr) {
        // Spawn actor for indicator if it does not already exist
        if (IndicatorMarker->SpawnedActor == nullptr) {
            ReadMarkerForActor(IndicatorMarker);
        }
        // else just update the indicator
        else {
            IndicatorMarker->UpdateTransform(minimapCellSize);
        }
    }
}



AActor* ADungeonMinimap::ReadMarkerForActor(DungeonObjectMarker *Marker)
{

    if (Marker->SpawnedActor) {
        return Marker->SpawnedActor;
    }

    // Setup Actor Params
    FActorSpawnParameters Params;
    Params.Owner = this->GetOwner();
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    UClass* MarkerClass = Marker->GetObjectTemplate();

    AActor *SpawnedActor = GetWorld()->SpawnActor<AActor>(MarkerClass, FTransform(), Params);
    SpawnedActor->AttachToComponent(SpawnRoot, FAttachmentTransformRules::KeepRelativeTransform);

    // Scale isn't always properly set in SpawnActor, so we set it after spawning
    SpawnedActor->SetActorRelativeTransform(Marker->GetNormalizedTransform(minimapCellSize));

    Marker->SpawnedActor = SpawnedActor;

    return SpawnedActor;
}



void ADungeonMinimap::ConsumeMarkerForMesh(DungeonStaticMeshMarker *Marker)
{
    UInstancedStaticMeshComponent* InstancedStaticMesh;
    // Setup new instanced static mesh
    if (!MinimapMeshInstances.Contains(Marker->ObjectMesh)) {
        InstancedStaticMesh = NewObject<UInstancedStaticMeshComponent>(this);
        InstancedStaticMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
        InstancedStaticMesh->AttachToComponent(SpawnRoot, FAttachmentTransformRules::KeepRelativeTransform);
        InstancedStaticMesh->SetStaticMesh(Marker->ObjectMesh);
        InstancedStaticMesh->RegisterComponent();
        MinimapMeshInstances.Add(Marker->ObjectMesh, InstancedStaticMesh);
    }
    // or get existing one that matches the specified mesh
    else {
        InstancedStaticMesh = MinimapMeshInstances[Marker->ObjectMesh];
    }

    InstancedStaticMesh->AddInstance(Marker->GetNormalizedTransform(minimapCellSize));

    delete Marker;
}