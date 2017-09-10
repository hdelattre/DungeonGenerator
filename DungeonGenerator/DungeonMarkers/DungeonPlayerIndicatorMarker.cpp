// Copyright 2016-2017 Bazel Games

#include "Wizz.h"
#include "DungeonPlayerIndicatorMarker.h"

DungeonPlayerIndicatorMarker::DungeonPlayerIndicatorMarker()
{
}

DungeonPlayerIndicatorMarker::DungeonPlayerIndicatorMarker(AActor* Indicated, USceneComponent* RotationComponent, float dungeonCellSize, float displayCellSize)
{
    IndicatedActor = Indicated;
    IndicatedRotComponent = RotationComponent;
    indicatedCellSize = dungeonCellSize;

    Rotation = FRotator(0.0f);
    UpdateTransform(displayCellSize);
}

DungeonPlayerIndicatorMarker::~DungeonPlayerIndicatorMarker()
{
}

UClass* DungeonPlayerIndicatorMarker::GetObjectTemplate() const
{
    return Theme->PawnIndicator.Get();
}

void DungeonPlayerIndicatorMarker::UpdateTransform(float displayCellSize)
{
    DungeonFunctions::WorldToCellLocation(IndicatedActor->GetActorLocation(), indicatedCellSize, Location.X, Location.Y);
    Rotation.Yaw = IndicatedRotComponent->GetComponentRotation().Yaw;

    if (SpawnedActor != nullptr) {
        SpawnedActor->SetActorRelativeTransform(GetNormalizedTransform(displayCellSize));
    }
}
