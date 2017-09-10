// Copyright 2016-2017 Bazel Games

#pragma once

#include "DungeonCell.h"
#include "DungeonCellEdge.h"

/**
 * 
 */
class WIZZ_API DungeonSector
{
public:

    // The x, y cell at which this sector should start
    int32 originX;
    int32 originY;

    // The number of cells along the room's x, y axes
    int32 lengthY;
    int32 lengthX;

    // The z axis value at which the sector's floor will lie
    float height;

    // The total number of cells
    int32 size;

    // The probability that any cell will have an edge cycling back to a previous cell
    float CycleProbability;

    TSet<DungeonCellEdge> Edges;

	DungeonSector();
	~DungeonSector();

    DungeonSector(int32 originX, int32 originY, int32 lengthX, int32 lengthY, float cycleProbability);

    void GenerateSector(int32 startX = 0, int32 startY = 0);

    bool Contains(const DungeonCell& Cell) const;

private:

    FORCEINLINE int32 GetIndex(int32 x, int32 y) const;

    bool Validate(const DungeonCellEdge &Edge) const;

    bool Validate(const DungeonCell &Cell) const;

    TArray<DungeonCellEdge> GetNeighborEdges(const DungeonCell &Cell);
};
