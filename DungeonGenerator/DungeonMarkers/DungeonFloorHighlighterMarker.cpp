// Copyright 2016-2017 Bazel Games

#include "Wizz.h"
#include "DungeonFloorHighlighterMarker.h"

DungeonFloorHighlighterMarker::DungeonFloorHighlighterMarker()
{
}

DungeonFloorHighlighterMarker::DungeonFloorHighlighterMarker(const FVector &Location, const FRotator &Rotation)
    : DungeonObjectMarker(Location, Rotation)
{
}

DungeonFloorHighlighterMarker::~DungeonFloorHighlighterMarker()
{
    if (SpawnedActor != nullptr) {
        SpawnedActor->Destroy();
    }
}

bool DungeonFloorHighlighterMarker::UseInMinimap() const
{
    return false;
}

UClass* DungeonFloorHighlighterMarker::GetObjectTemplate() const
{
    return Theme->FloorHighlighter.Get();
}