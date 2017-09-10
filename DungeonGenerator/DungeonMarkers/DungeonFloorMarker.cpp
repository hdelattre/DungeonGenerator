// Copyright 2016-2017 Bazel Games

#include "Wizz.h"
#include "DungeonFloorMarker.h"

DungeonFloorMarker::DungeonFloorMarker()
{
}

DungeonFloorMarker::DungeonFloorMarker(const FVector &Location, const FRotator &Rotation)
    : DungeonStaticMeshMarker(Location, Rotation)
{
}

DungeonFloorMarker::~DungeonFloorMarker()
{
}

UStaticMesh* DungeonFloorMarker::GetMeshFromTheme()
{
    if (Theme != nullptr) {
        int index = ((int32)Location.X % 2 + (int32)Location.Y % 2) % 2;

        UStaticMesh* Mesh = Cast<UStaticMesh>(Theme->FloorMeshes[index].Mesh);
        //UStaticMesh* Mesh = Theme->GetRandomMesh(Theme->FloorMeshes);

        if (Mesh != nullptr) {
            SetMesh(Mesh);
        }
    }

    return ObjectMesh;
}

bool DungeonFloorMarker::UseInMinimap() const
{
    return true;
}

FVector DungeonFloorMarker::GetMeshPivot() const
{
    FBoxSphereBounds Bounds = ObjectMesh->GetBounds();
    FVector Origin = Bounds.Origin;
    FVector Extent = Bounds.BoxExtent;

    return FVector(Origin.X, Origin.Y, Origin.Z + Extent.Z);
}

FTransform DungeonFloorMarker::GetNormalizedTransform(float cellSize) const
{
    FTransform NormTransform;

    FBoxSphereBounds Bounds = ObjectMesh->GetBounds();
    FVector MeshExtent = Bounds.BoxExtent;
    FVector MeshOrigin = Bounds.Origin;

    // Normalize Scale
    FVector NormScale(1.0f);
    NormScale.X = cellSize / (2.0f * MeshExtent.X);
    NormScale.Y = cellSize / (2.0f * MeshExtent.Y);
    NormScale.Z = DUNGEON_FLOOR_THICKNESS / (2.0f * MeshExtent.Z);
    NormTransform.SetScale3D(NormScale);

    // Normalize Location
    FVector NormLocation = GetLocation();
    NormLocation.X *= cellSize;
    NormLocation.Y *= cellSize;
    
    NormLocation -= PivotOffset * NormScale;

    NormTransform.SetLocation(NormLocation);
    NormTransform.SetRotation(GetRotation().Quaternion());

    return NormTransform;
}

const FName DungeonFloorMarker::GetFolderString() const
{
    return TEXT("/Dungeon/Floor");
}