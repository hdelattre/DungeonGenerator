// Copyright 2016-2017 Hunter Delattre

#include "Wizz.h"
#include "DungeonObjectMarker.h"

DungeonObjectMarker::DungeonObjectMarker()
{
    this->Location = FVector(0.0f);
    this->Rotation = FRotator(0.0f);
}

DungeonObjectMarker::DungeonObjectMarker(const FVector &Location, const FRotator &Rotation)
{
    this->Location = Location;
    this->Rotation = Rotation;
}

DungeonObjectMarker::~DungeonObjectMarker()
{
    if (SpawnedActor != nullptr) {
        SpawnedActor->Destroy();
    }
}

bool DungeonObjectMarker::SetTheme(UDungeonTheme *NewTheme)
{
    Theme = NewTheme;

    return NewTheme != nullptr;
}

bool DungeonObjectMarker::UseInMinimap() const
{
    return false;
}

UClass* DungeonObjectMarker::GetObjectTemplate() const
{
    return nullptr;
}

void DungeonObjectMarker::SetupNewActor(AActor* NewActor) const
{
    
}

FTransform DungeonObjectMarker::GetNormalizedTransform(float cellSize) const
{
    FTransform NormTransform;

    // Normalize Scale
    FVector NormScale(cellSize / DUNGEON_ASSUMED_OBJECT_SCALE);
    NormTransform.SetScale3D(NormScale);

    // Normalize Location
    FVector NormLocation = GetLocation();
    NormLocation.X *= cellSize;
    NormLocation.Y *= cellSize;

    NormTransform.SetLocation(NormLocation);
    NormTransform.SetRotation(GetRotation().Quaternion());

    return NormTransform;
}

const FName DungeonObjectMarker::GetFolderString() const
{
    return TEXT("/Dungeon/Other");
}






FTransform DungeonObjectMarker::GetTransform() const
{
    return FTransform(Rotation, Location);
}

FVector DungeonObjectMarker::GetLocation() const
{
    return Location;
}

FRotator DungeonObjectMarker::GetRotation() const
{
    return Rotation;
}