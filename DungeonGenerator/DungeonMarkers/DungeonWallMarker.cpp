// Copyright 2016-2017 Bazel Games

#include "Wizz.h"
#include "DungeonWallMarker.h"

DungeonWallMarker::DungeonWallMarker()
{
}

DungeonWallMarker::DungeonWallMarker(const FVector &Location, const FRotator &Rotation)
    : DungeonStaticMeshMarker(Location, Rotation)
{
}

DungeonWallMarker::~DungeonWallMarker()
{
}

UStaticMesh* DungeonWallMarker::GetMeshFromTheme()
{
    if (Theme != nullptr) {
        UStaticMesh* Mesh = Theme->GetRandomMesh(Theme->WallMeshes);

        if (Mesh != nullptr) {
            SetMesh(Mesh);
        }
    }

    return ObjectMesh;
}

bool DungeonWallMarker::UseInMinimap() const
{
    return true;
}

FVector DungeonWallMarker::GetMeshPivot() const
{
    FBoxSphereBounds Bounds = ObjectMesh->GetBounds();
    FVector Origin = Bounds.Origin;
    FVector Extent = Bounds.BoxExtent;

    return FVector(Origin.X, Origin.Y, Origin.Z - Extent.Z);
}

FTransform DungeonWallMarker::GetNormalizedTransform(float cellSize) const
{
    FTransform NormTransform;

    FBoxSphereBounds Bounds = ObjectMesh->GetBounds();
    FVector MeshExtent = Bounds.BoxExtent;
    FVector MeshOrigin = Bounds.Origin;

    // Normalize Scale
    FVector NormScale(1.0f);
    NormScale.X = (cellSize * .9) / (2.0f * MeshExtent.X);
    NormScale.Y = cellSize / (2.0f * MeshExtent.Y) / 10;
    NormScale.Z = (cellSize + DUNGEON_FLOOR_THICKNESS) / (2.0f * MeshExtent.Z) * Theme->WallHeight;
    
    NormTransform.SetScale3D(NormScale);

    // Normalize Location
    FVector NormLocation = GetLocation();
    NormLocation.X *= cellSize;
    NormLocation.Y *= cellSize;

    if (Rotation.Yaw == 0) {
        NormTransform.SetRotation(FRotator(0.0f).Quaternion());
        NormLocation -= PivotOffset * NormScale;

        NormLocation.Y -= cellSize * .5;
    }
    else {
        FQuat RotQuat = FRotator(0.0f, 90.0f, 0.0f).Quaternion();
        NormTransform.SetRotation(RotQuat);
        FVector Adj = RotQuat.RotateVector(PivotOffset * NormScale);
        NormLocation.X += Adj.X;
        NormLocation.Y -= Adj.Y;
        NormLocation.Z -= Adj.Z; 

        NormLocation.X -= cellSize * .5;
    }

    // Move down so walls cover up floors
    NormLocation.Z -= DUNGEON_FLOOR_THICKNESS;

    NormTransform.SetLocation(NormLocation);
    

    return NormTransform;
}

const FName DungeonWallMarker::GetFolderString() const
{
    return TEXT("/Dungeon/Wall");
}