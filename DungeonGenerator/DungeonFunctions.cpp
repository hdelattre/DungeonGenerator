// Copyright 2016-2017 Hunter Delattre

#include "Wizz.h"
#include "DungeonFunctions.h"

DungeonFunctions::DungeonFunctions()
{
}

DungeonFunctions::~DungeonFunctions()
{
}

FVector DungeonFunctions::WorldToCellLocation(const FVector& WorldLocation, float cellSize)
{
    FVector CellLocation;

    CellLocation.X = FMath::RoundToInt(WorldLocation.X / cellSize);
    CellLocation.Y = FMath::RoundToInt(WorldLocation.Y / cellSize);
    CellLocation.Z = WorldLocation.Z;

    return CellLocation;
}

void DungeonFunctions::WorldToCellLocation(const FVector& WorldLocation, float cellSize, int32& CellX, int32& CellY)
{
    DungeonCell LocationCell(WorldLocation, cellSize);
    CellX = LocationCell.x;
    CellY = LocationCell.y;
}

void DungeonFunctions::WorldToCellLocation(const FVector& WorldLocation, float cellSize, float& CellX, float& CellY)
{
    int32 X, Y;
    WorldToCellLocation(WorldLocation, cellSize, X, Y);

    CellX = X;
    CellY = Y;
}

FVector DungeonFunctions::CellToWorldLocation(const FVector& CellLocation, float cellSize)
{
    FVector WorldLocation = CellLocation;
    WorldLocation.X *= cellSize;
    WorldLocation.Y *= cellSize;

    return WorldLocation;
}

FVector DungeonFunctions::CellToWorldLocation(const DungeonCell& Cell, float cellSize)
{
    return FVector(Cell.x * cellSize, Cell.y * cellSize, 0);
}

TArray<DungeonCell> DungeonFunctions::GetNeighborCells(const DungeonCell& Cell, const DungeonSector& Sector, const TArray<EEdgeDirection>& Order)
{
    TArray<DungeonCell> Neighbors;

    TArray<DungeonCellEdge> NeighborEdges = {
        DungeonCellEdge(Cell.x, Cell.y, Order[0]),
        DungeonCellEdge(Cell.x, Cell.y, Order[1]),
        DungeonCellEdge(Cell.x, Cell.y, Order[2]),
        DungeonCellEdge(Cell.x, Cell.y, Order[3])
    };

    for (DungeonCellEdge NeighborEdge : NeighborEdges) {
        if (Sector.Edges.Contains(NeighborEdge)) {
            Neighbors.Add(NeighborEdge.GetEndCell());
        }
    }

    return Neighbors;
}

TArray<DungeonCell> DungeonFunctions::GetCellPath(DungeonCell StartCell, DungeonCell EndCell, const DungeonSector& Sector, const EDungeonPathBias& Bias)
{
    if (!Sector.Contains(EndCell)) {
        return TArray<DungeonCell>();
    }

    TArray<EEdgeDirection> NeighborSearchOrder = GetNeighborOrder(StartCell, EndCell, Bias);

    // Center search orders need to be readjusted constantly to account for changes in direction
    bool alwaysUpdateOrder = (Bias == EDungeonPathBias::CenterLeft || Bias == EDungeonPathBias::CenterRight);

    TArray<DungeonCell> OpenSet;
    TSet<DungeonCell> ClosedSet;
    TMap<DungeonCell, float> Scores;
    TMap<DungeonCell, DungeonCell> CameFrom;

    StartCell.distance = 0;
    StartCell.heuristic = StartCell.ManhattanDistance(EndCell);

    OpenSet.HeapPush(StartCell);
    Scores.Add(StartCell, 0);

    // A* Search
    while (OpenSet.Num() > 0) {

        DungeonCell CurrentCell;

        OpenSet.HeapPop(CurrentCell);

        // reconstruct path if we finished
        if (CurrentCell == EndCell) {

            TArray<DungeonCell> Path;

            DungeonCell PathCell = CurrentCell;
            while (PathCell != StartCell) {

                Path.Insert(PathCell, 0);

                PathCell = CameFrom[PathCell];
            }

            return Path;
        }

        ClosedSet.Add(CurrentCell);

        if (alwaysUpdateOrder) {
            NeighborSearchOrder = GetNeighborOrder(CurrentCell, EndCell, Bias);
        }

        // Use to adjust heuristic so neighbors earlier in the search order will be processed first
        float orderPreference = 0;

        for (DungeonCell Neighbor : GetNeighborCells(CurrentCell, Sector, NeighborSearchOrder)) {

            orderPreference++;

            // ignore processed nodes
            if (ClosedSet.Contains(Neighbor)) {
                continue;
            }

            //Neighbor.distance = Scores[CurrentCell] + 1;
            Neighbor.distance = Neighbor.EuclideanDistance(StartCell);
            Neighbor.heuristic = Neighbor.EuclideanDistance(EndCell) + orderPreference * .01;

            if (!OpenSet.Contains(Neighbor)) {
                OpenSet.HeapPush(Neighbor);
            }
            else if (Neighbor.distance >= Scores[Neighbor]) {
                continue;
            }

            CameFrom.Add(Neighbor, CurrentCell);
            Scores.Add(Neighbor, Neighbor.distance);
        }
    }

    // failure
    return TArray<DungeonCell>();
}

EEdgeDirection DungeonFunctions::NumToEdgeDirection(uint8 direction)
{
    direction = direction % 4;
    
    switch (direction) {
        case 0: return EEdgeDirection::XPlus;
        case 1: return EEdgeDirection::YPlus;
        case 2: return EEdgeDirection::XMinus;
        case 3: return EEdgeDirection::YMinus;
        default: return EEdgeDirection::XPlus;
    }
}


TArray<EEdgeDirection> DungeonFunctions::GetNeighborOrder(const DungeonCell& StartCell, const DungeonCell& EndCell, const EDungeonPathBias& Bias)
{
    int32 DiffX = EndCell.x - StartCell.x;
    int32 DiffY = EndCell.y - StartCell.y;

    uint8 startDirection;

    int32 XMag = FMath::Abs(DiffX);
    int32 YMag = FMath::Abs(DiffY);

    if (XMag >= YMag) {
        if (DiffX > 0) {
            startDirection = 0;
        }
        else {
            startDirection = 2;
        }
    }
    else {
        if (DiffY > 0) {
            startDirection = 1;
        }
        else {
            startDirection = 3;
        }
    }

    // The >= check above defers to X when magnitudes are equal, which constitutes a leftward bias
    // when pointing toward a cell at a diagonal from you. For rightward pathing biases we want this
    // to be a rightward bias instead, so we turn the starting direction one to the right
    if (XMag == YMag && (Bias == EDungeonPathBias::Right || Bias == EDungeonPathBias::CenterRight)) {
        startDirection++;
    }

    switch (Bias) {
    case EDungeonPathBias::CenterLeft:
        return TArray<EEdgeDirection>() = {
            NumToEdgeDirection(startDirection),
            NumToEdgeDirection(startDirection - 1),
            NumToEdgeDirection(startDirection + 1),
            NumToEdgeDirection(startDirection + 2)
        };
    case EDungeonPathBias::CenterRight:
        return TArray<EEdgeDirection>() = {
            NumToEdgeDirection(startDirection),
            NumToEdgeDirection(startDirection + 1),
            NumToEdgeDirection(startDirection - 1),
            NumToEdgeDirection(startDirection + 2)
        };
    case EDungeonPathBias::Left:
        return TArray<EEdgeDirection>() = {
            NumToEdgeDirection(startDirection - 1),
            NumToEdgeDirection(startDirection),
            NumToEdgeDirection(startDirection + 1),
            NumToEdgeDirection(startDirection + 2)
        };
    case EDungeonPathBias::Right:
        return TArray<EEdgeDirection>() = {
            NumToEdgeDirection(startDirection + 1),
            NumToEdgeDirection(startDirection),
            NumToEdgeDirection(startDirection - 1),
            NumToEdgeDirection(startDirection + 2)
        };
    default:
        return DEFAULT_EDGE_ORDER;
    }
}

TArray<FVector> DungeonFunctions::CellsToLocations(const TArray<DungeonCell>& Cells, float cellSize)
{
    TArray<FVector> Locations;
    Locations.Reserve(Cells.Num());

    for (int ii = 0; ii < Cells.Num(); ii++)
    {
        Locations.Add(CellToWorldLocation(Cells[ii], cellSize));
    }

    return Locations;
}

TArray<DungeonCell> DungeonFunctions::LocationsToCells(const TArray<FVector>& Locations, float cellSize)
{
    TArray<DungeonCell> Cells;
    Cells.Reserve(Locations.Num());

    for (int ii = 0; ii < Locations.Num(); ii++)
    {
        Cells.Add(DungeonCell(Locations[ii], cellSize));
    }

    return Cells;
}

EDungeonPathBias DungeonFunctions::InferPathBias(const FVector& StartLocation, const FVector& EndLocation, float cellSize)
{
    FVector StartCellLocation = WorldToCellLocation(StartLocation, cellSize);
    FVector EndCellLocation = WorldToCellLocation(EndLocation, cellSize);

    FVector LocationDiff = EndLocation - StartCellLocation;
    FVector CellDiff = EndCellLocation - StartCellLocation;

    float CellAngle = FMath::Atan2(CellDiff.Y, CellDiff.X);
    float GoalAngle = FMath::Atan2(LocationDiff.Y, LocationDiff.X);

    if (FMath::Abs(GoalAngle - CellAngle) < PATHING_BIAS_CENTER_ANGLE) {
        if (GoalAngle < CellAngle) {
            return EDungeonPathBias::CenterLeft;
        }
        else {
            return EDungeonPathBias::CenterRight;
        }

    }
    else if (GoalAngle < CellAngle) {
        return EDungeonPathBias::Left;
    }
    else {
        return EDungeonPathBias::Right;
    }
}