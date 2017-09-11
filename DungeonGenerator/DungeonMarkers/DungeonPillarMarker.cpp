// Copyright 2016-2017 Hunter Delattre

#include "Wizz.h"
#include "DungeonPillarMarker.h"

DungeonPillarMarker::DungeonPillarMarker()
{
}

DungeonPillarMarker::DungeonPillarMarker(const FVector &Location, const FRotator &Rotation)
    : DungeonStaticMeshMarker(Location, Rotation)
{
}

DungeonPillarMarker::~DungeonPillarMarker()
{
}

UStaticMesh* DungeonPillarMarker::GetMeshFromTheme()
{
    if (Theme != nullptr) {
        UStaticMesh* Mesh = Theme->GetRandomMesh(Theme->PillarMeshes);

        if (Mesh != nullptr) {
            SetMesh(Mesh);
        }
    }

    return ObjectMesh;
}

bool DungeonPillarMarker::UseInMinimap() const
{
    return true;
}

FVector DungeonPillarMarker::GetMeshPivot() const
{
    FBoxSphereBounds Bounds = ObjectMesh->GetBounds();
    FVector Origin = Bounds.Origin;
    FVector Extent = Bounds.BoxExtent;

    return FVector(Origin.X, Origin.Y, Origin.Z - Extent.Z);
}

FTransform DungeonPillarMarker::GetNormalizedTransform(float cellSize) const
{
    FTransform NormTransform;

    FBoxSphereBounds Bounds = ObjectMesh->GetBounds();
    FVector MeshExtent = Bounds.BoxExtent;
    FVector MeshOrigin = Bounds.Origin;

    // Normalize Scale
    FVector NormScale(1.0f);
    NormScale.X = cellSize / (20 * MeshExtent.X) * Theme->PillarSize;
    NormScale.Y = cellSize / (20 * MeshExtent.Y) * Theme->PillarSize;
    NormScale.Z = (cellSize + DUNGEON_FLOOR_THICKNESS) / (2 * MeshExtent.Z) * Theme->PillarHeight;

    NormTransform.SetScale3D(NormScale);

    // Normalize Location
    FVector NormLocation = GetLocation();
    NormLocation.X *= cellSize;
    NormLocation.Y *= cellSize;

    NormLocation.X -= cellSize * .5;
    NormLocation.Y -= cellSize *.5;

    NormLocation -= PivotOffset * NormScale;

    // Move down so pillars cover up floors
    NormLocation.Z -= DUNGEON_FLOOR_THICKNESS;

    NormTransform.SetLocation(NormLocation);
    NormTransform.SetRotation(FRotator(0.0f).Quaternion());

    return NormTransform;
}

const FName DungeonPillarMarker::GetFolderString() const
{
    return TEXT("/Dungeon/Pillar");
}