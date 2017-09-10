// Copyright 2016-2017 Bazel Games

#pragma once

#include "DungeonCell.h"

enum class EEdgeDirection : uint8
{
    XPlus,
    XMinus,
    YPlus,
    YMinus
};


/**
 * 
 */
class WIZZ_API DungeonCellEdge
{
public:

    const static int32 MAX_DUNGEON_EDGE_POSITION = DungeonCell::MAX_DUNGEON_CELL_POSITION * 2;

    int32 x;
    int32 y;

    EEdgeDirection Direction;

	DungeonCellEdge(int32 x, int32 y, EEdgeDirection Direction);
    DungeonCellEdge(uint32 hash);
    ~DungeonCellEdge();

    friend uint32 GetTypeHash(const DungeonCellEdge& Edge)
    {
        uint32 edgeX = (2 * Edge.x) + 1;
        uint32 edgeY = (2 * Edge.y) + 1;

        switch (Edge.Direction) {
        case EEdgeDirection::XPlus:  edgeX += 1; break;
        case EEdgeDirection::XMinus: edgeX -= 1; break;
        case EEdgeDirection::YPlus:  edgeY += 1; break;
        case EEdgeDirection::YMinus: edgeY -= 1;
        }

        return edgeX * DungeonCellEdge::MAX_DUNGEON_EDGE_POSITION + edgeY;
    };

    bool operator==(const DungeonCellEdge &Other) const
    {
        return GetTypeHash(*this) == GetTypeHash(Other);
    };

    DungeonCell GetHomeCell() const;

    DungeonCell GetEndCell() const;
};
