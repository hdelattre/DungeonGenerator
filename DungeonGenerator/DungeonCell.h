// Copyright 2016-2017 Bazel Games

#pragma once

/**
 * A cell is a node representing a floor space in the dungeon.
 */
class WIZZ_API DungeonCell
{
public:

    const static int32 MAX_DUNGEON_CELL_POSITION = 1024;

    int32 x;
    int32 y;

    float distance = 0;
    float heuristic = 0;

	DungeonCell();
    DungeonCell(int32 x, int32 y);
    DungeonCell(FVector Location, float CellSize);
    DungeonCell(const DungeonCell &Copy);
	~DungeonCell();

    FORCEINLINE friend uint32 GetTypeHash(const DungeonCell& Cell)
    {
        return (Cell.x * DungeonCell::MAX_DUNGEON_CELL_POSITION) + Cell.y;
    };

    bool operator==(const DungeonCell& Other) const
    {
        return x == Other.x && y == Other.y;
    };

    bool operator!=(const DungeonCell &Other) const
    {
        return !(*this == Other);
    };

    bool operator<(const DungeonCell& Other) const
    {
        return (distance + heuristic) < (Other.distance + Other.heuristic);
    };

    int32 ManhattanDistance(const DungeonCell& EndCell)
    {
        return FMath::Abs(x - EndCell.x) + FMath::Abs(y - EndCell.y);
    };

    float EuclideanDistance(const DungeonCell& EndCell)
    {
        return FVector2D::Distance(FVector2D(x, y), FVector2D(EndCell.x, EndCell.y));
    }

private:

    
};
