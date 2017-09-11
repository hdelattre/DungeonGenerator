// Copyright 2016-2017 Hunter Delattre

#include "Wizz.h"
#include "DungeonStaticMeshMarker.h"

DungeonStaticMeshMarker::DungeonStaticMeshMarker()
{
}

DungeonStaticMeshMarker::DungeonStaticMeshMarker(const FVector &Location, const FRotator &Rotation)
    : DungeonObjectMarker(Location, Rotation)
{

}

DungeonStaticMeshMarker::~DungeonStaticMeshMarker()
{
}

bool DungeonStaticMeshMarker::SetTheme(UDungeonTheme *NewTheme)
{
    Theme = NewTheme;

    return GetMeshFromTheme() != nullptr;
}

void DungeonStaticMeshMarker::SetMesh(UStaticMesh *Mesh)
{
    this->ObjectMesh = Mesh;
    this->PivotOffset = GetMeshPivot();
}

UStaticMesh* DungeonStaticMeshMarker::GetMeshFromTheme()
{
    return nullptr;
}

FVector DungeonStaticMeshMarker::GetMeshPivot() const
{
    FBoxSphereBounds Bounds = ObjectMesh->GetBounds();
    FVector Origin = Bounds.Origin;
    FVector Extent = Bounds.BoxExtent;

    return FVector(Origin.X, Origin.Y, Origin.Z - Extent.Z);
}

FTransform DungeonStaticMeshMarker::GetNormalizedTransform(float cellSize) const
{
    FTransform NormTransform;

    FBoxSphereBounds Bounds = ObjectMesh->GetBounds();
    FVector MeshExtent = Bounds.BoxExtent;
    FVector MeshOrigin = Bounds.Origin;

    // Normalize Scale
    FVector NormScale(1.0f);
    NormTransform.SetScale3D(NormScale);

    // Normalize Location
    FVector NormLocation = GetLocation();
    NormLocation.X *= cellSize;
    NormLocation.Y *= cellSize;

    NormTransform.SetLocation(NormLocation - PivotOffset * NormScale);
    NormTransform.SetRotation(GetRotation().Quaternion());

    return NormTransform;
}