// Copyright 2016-2017 Hunter Delattre

#include "Wizz.h"
#include "DungeonMinimapIndicatorMarker.h"

DungeonMinimapIndicatorMarker::DungeonMinimapIndicatorMarker()
{
}

DungeonMinimapIndicatorMarker::DungeonMinimapIndicatorMarker(AActor* Indicated, float dungeonCellSize, float displayCellSize)
{
    IndicatedActor = Indicated;
    indicatedCellSize = dungeonCellSize;

    UpdateTransform(dungeonCellSize);
}

DungeonMinimapIndicatorMarker::~DungeonMinimapIndicatorMarker()
{
}

bool DungeonMinimapIndicatorMarker::UseInMinimap() const
{
    return true;
}

UClass* DungeonMinimapIndicatorMarker::GetObjectTemplate() const
{
    return Theme->ObjectIndicator.Get();
}

void DungeonMinimapIndicatorMarker::UpdateTransform(float displayCellSize)
{
    DungeonFunctions::WorldToCellLocation(IndicatedActor->GetActorLocation(), indicatedCellSize, Location.X, Location.Y);

    if (SpawnedActor != nullptr) {
        SpawnedActor->SetActorRelativeTransform(GetNormalizedTransform(displayCellSize));
    }
}