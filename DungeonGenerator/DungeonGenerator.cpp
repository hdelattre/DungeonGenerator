
// Copyright 2016-2017 Hunter Delattre

#include "Wizz.h"
#include "DungeonGenerator.h"

// Sets default values
ADungeonGenerator::ADungeonGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void ADungeonGenerator::BeginPlay()
{
	Super::BeginPlay();

    GenerateSectors();

    BuildDungeon();
}

// Called every frame
void ADungeonGenerator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}



FVector ADungeonGenerator::GetCellCenter(FVector Location) const
{
    return DungeonFunctions::CellToWorldLocation(DungeonFunctions::WorldToCellLocation(Location, cellSize), cellSize);
}


TArray<FVector> ADungeonGenerator::GetCellPath(FVector StartLocation, FVector EndLocation) const
{
    return DungeonFunctions::GetCellPathLocations(StartLocation, EndLocation, cellSize, *CurrentSector);
}

DungeonSector* ADungeonGenerator::GetCurrentSector() const
{
    return CurrentSector;
}




/******************************
*    GENERATION
*******************************/


void ADungeonGenerator::BuildDungeon()
{
    if (DungeonTheme == nullptr) {
        UE_LOG(LogActor, Warning, TEXT("No theme was assigned to Dungeon Generator."));
        return;
    }

    for (int ii = 0; ii < Sectors.Num(); ii++) {
        SpawnSector(Sectors[ii]);
    }
}


void ADungeonGenerator::GenerateSectors()
{
    if (LayoutSeed > 0) {
        FMath::RandInit(LayoutSeed);
    }

    DungeonSector NewSector(0, 0, SectorXLength, SectorYLength, CycleProbability);
    NewSector.GenerateSector(0, 0);
    Sectors.Add(NewSector);

    CurrentSector = &Sectors[0];
}





/******************************
*    SPAWNING
*******************************/

void ADungeonGenerator::SpawnSector(const DungeonSector &Sector)
{
    for (DungeonStaticMeshMarker* Marker : DungeonMarkerProducer::CreateSectorArchitectureMarkers(Sector)) {
        Marker->SetTheme(DungeonTheme);
        ConsumeMarkerForMesh(Marker, this);
    }

    for (TPair<UStaticMesh*, UInstancedStaticMeshComponent*> Entry : DungeonMeshInstances) {
        Entry.Value->SetStaticMesh(Entry.Key);
        Entry.Value->RegisterComponent();
    }

    // navmesh won't generate if we don't move (todo get rid of this)
    this->SetActorLocation(FVector(1.0f));
    this->SetActorLocation(FVector(0.0f));
}


AActor* ADungeonGenerator::ConsumeMarkerForActor(DungeonObjectMarker* Marker, AActor* Outer)
{
    AActor* SpawnedActor = ReadMarkerForActor(Marker, Outer);
    delete Marker;
    return SpawnedActor;
}

void ADungeonGenerator::ConsumeMarkerForMesh(DungeonStaticMeshMarker* Marker, AActor* Outer)
{
    UInstancedStaticMeshComponent* InstancedStaticMesh;
    // Setup new instanced static mesh
    if (!DungeonMeshInstances.Contains(Marker->ObjectMesh)) {
        if (Outer == nullptr) {
            Outer = this;
        }
        InstancedStaticMesh = NewObject<UInstancedStaticMeshComponent>(Outer);
        InstancedStaticMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
        DungeonMeshInstances.Add(Marker->ObjectMesh, InstancedStaticMesh);
    }
    // or get existing one that matches the specified mesh
    else {
        InstancedStaticMesh = DungeonMeshInstances[Marker->ObjectMesh];
    }

    InstancedStaticMesh->AddInstance(Marker->GetNormalizedTransform(cellSize));

    delete Marker;
}

AActor* ADungeonGenerator::ReadMarkerForActor(DungeonObjectMarker *Marker, AActor* Outer)
{
    // Setup Actor Params
    FActorSpawnParameters Params;
    Params.Owner = Outer;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    UClass* MarkerClass = Marker->GetObjectTemplate();

    AActor *SpawnedActor = GetWorld()->SpawnActor<AActor>(MarkerClass, FTransform(), Params);

    // Scale isn't always properly set in SpawnActor
    SpawnedActor->SetActorTransform(Marker->GetNormalizedTransform(cellSize));

    return SpawnedActor;
}


