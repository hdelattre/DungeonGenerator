// Copyright 2016-2017 Hunter Delattre

#include "Wizz.h"
#include "DungeonMarkerProducer.h"

DungeonMarkerProducer::DungeonMarkerProducer()
{
}

DungeonMarkerProducer::~DungeonMarkerProducer()
{
}

TArray<DungeonObjectMarker*> DungeonMarkerProducer::CreateSectorMarkers(const DungeonSector& Sector)
{
    return TArray<DungeonObjectMarker*>();
}

TArray<DungeonStaticMeshMarker*> DungeonMarkerProducer::CreateSectorArchitectureMarkers(const DungeonSector& Sector)
{
    TArray<DungeonStaticMeshMarker*> Markers;

    // Floor Markers
    for (int iy = 0; iy < Sector.lengthY; iy++) {
        for (int ix = 0; ix < Sector.lengthX; ix++) {
            FVector Location(Sector.originX + ix, Sector.originY + iy, Sector.height);

            Markers.Add(new DungeonFloorMarker(Location, FRotator(0.0f)));
        }
    }

    FRotator XAlignedRotation(0.0f, 00.0f, 0.0f);
    FRotator YAlignedRotation(0.0f, 90.0f, 0.0f);

    // Maze Walls and Pillars
    for (int iy = 0; iy < Sector.lengthY; iy++) {
        for (int ix = 0; ix < Sector.lengthX; ix++) {
            FVector Location(Sector.originX + ix, Sector.originY + iy, Sector.height);

            if (!Sector.Edges.Contains(DungeonCellEdge(ix, iy, EEdgeDirection::XMinus))) {
                Markers.Add(new DungeonWallMarker(Location, YAlignedRotation));
            }
            if (!Sector.Edges.Contains(DungeonCellEdge(ix, iy, EEdgeDirection::YMinus))) {
                Markers.Add(new DungeonWallMarker(Location, XAlignedRotation));
            }
            if (!Sector.Edges.Contains(DungeonCellEdge(ix, iy, EEdgeDirection::XMinus)) ||
                !Sector.Edges.Contains(DungeonCellEdge(ix, iy, EEdgeDirection::YMinus)) ||
                !Sector.Edges.Contains(DungeonCellEdge(ix - 1, iy, EEdgeDirection::YMinus)) ||
                !Sector.Edges.Contains(DungeonCellEdge(ix, iy - 1, EEdgeDirection::XMinus))) {
                Markers.Add(new DungeonPillarMarker(Location, FRotator(0.0f)));
            }

        }
    }

    // Border Walls Along X axis
    for (int ix = 0; ix < Sector.lengthX; ix++) {
        FVector Location(Sector.originX + ix, Sector.originY + Sector.lengthY, Sector.height);
        Markers.Add(new DungeonWallMarker(Location, XAlignedRotation));
        Markers.Add(new DungeonPillarMarker(Location, FRotator(0.0f)));
    }
    // Border Walls Along Y axis
    for (int iy = 0; iy < Sector.lengthY; iy++) {
        FVector Location(Sector.originX + Sector.lengthX, Sector.originY + iy, Sector.height);
        Markers.Add(new DungeonWallMarker(Location, YAlignedRotation));
        Markers.Add(new DungeonPillarMarker(Location, FRotator(0.0f)));
    }

    // Last Corner Pillar
    Markers.Add(new DungeonPillarMarker(FVector(Sector.originX + Sector.lengthX, Sector.originY + Sector.lengthY, Sector.height), FRotator(0.0f)));

    return Markers;
}