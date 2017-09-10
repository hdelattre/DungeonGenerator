// Copyright 2016-2017 Bazel Games

#include "Wizz.h"
#include "DungeonCell.h"

DungeonCell::DungeonCell()
{
}

DungeonCell::DungeonCell(int32 x, int32  y)
{
    this->x = x;
    this->y = y;
}

DungeonCell::DungeonCell(FVector Location, float CellSize)
{
    x = FMath::RoundToInt(Location.X / CellSize);
    y = FMath::RoundToInt(Location.Y / CellSize);
}

DungeonCell::DungeonCell(const DungeonCell &Copy)
{
    this->x = Copy.x;
    this->y = Copy.y;

    this->distance = Copy.distance;
    this->heuristic = Copy.heuristic;
}

DungeonCell::~DungeonCell()
{
}