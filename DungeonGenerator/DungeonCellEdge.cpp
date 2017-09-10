// Copyright 2016-2017 Bazel Games

#include "Wizz.h"
#include "DungeonCellEdge.h"

DungeonCellEdge::DungeonCellEdge(int32 x, int32 y, EEdgeDirection Direction)
{
    this->x = x;
    this->y = y;
    this->Direction = Direction;
}

DungeonCellEdge::DungeonCellEdge(uint32 hash)
{
    uint32 edgeX = hash / DungeonCellEdge::MAX_DUNGEON_EDGE_POSITION;
    uint32 edgeY = hash % DungeonCellEdge::MAX_DUNGEON_EDGE_POSITION;

    if (edgeX == 0) {
        x = 0;
        y = (edgeY - 1) / 2;
        Direction = EEdgeDirection::XMinus;
    }
    else if (edgeY == 0) {
        x = (edgeX - 1) / 2;
        y = 0;
        Direction = EEdgeDirection::YMinus;
    }
    else if (edgeX % 2 == 0) {
        x = (edgeX - 2) / 2;
        y = (edgeY - 1) / 2;
        EEdgeDirection::XPlus;
    }
    else {
        x = (edgeX - 1) / 2;
        y = (edgeY - 2) / 2;
        EEdgeDirection::YPlus;
    }
}

DungeonCellEdge::~DungeonCellEdge()
{
}

DungeonCell DungeonCellEdge::GetHomeCell() const
{
    return DungeonCell(x, y);
}

DungeonCell DungeonCellEdge::GetEndCell() const
{
    int32 otherX = x;
    int32 otherY = y;

    switch (Direction) {
        case EEdgeDirection::XPlus:  otherX += 1; break;
        case EEdgeDirection::XMinus: otherX -= 1; break;
        case EEdgeDirection::YPlus:  otherY += 1; break;
        case EEdgeDirection::YMinus: otherY -= 1;
    }

    return DungeonCell(otherX, otherY);
}