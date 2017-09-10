// Copyright 2016-2017 Bazel Games

#include "Wizz.h"
#include "DungeonSector.h"
#include "DungeonCellEdge.h"

const float ADJACENT_PROBABILITY = .45;

DungeonSector::DungeonSector()
{
}

DungeonSector::DungeonSector(int32 originX, int32 originY, int32 lengthX, int32 lengthY, float cycleProbability)
{
    this->originX = originX;
    this->originY = originY;
    this->lengthX = lengthX;
    this->lengthY = lengthY;
    this->size = lengthY * lengthX;
    this->height = 0.0f;
    this->CycleProbability = cycleProbability;
}

DungeonSector::~DungeonSector()
{
}


void DungeonSector::GenerateSector(int32 startX, int32 startY)
{
    TSet<DungeonCell> Processed;
    TArray<DungeonCell> CellStack;
    TArray<DungeonCell> SeenStack;

    CellStack.Push(DungeonCell(startX, startY));

    while (CellStack.Num() > 0 || SeenStack.Num() > 0) {

        DungeonCell CurrentCell;

        if (CellStack.Num() > 0) {
            CurrentCell = CellStack.Pop();
        }
        else {
            CurrentCell = SeenStack.Pop();
        }

        TArray<DungeonCellEdge> Neighbors = GetNeighborEdges(CurrentCell);

        while (Neighbors.Num() > 0) {
            int neighborIndex = FMath::RandRange(0, Neighbors.Num() - 1);
            DungeonCellEdge NeighborEdge = Neighbors[neighborIndex];
            Neighbors.RemoveAtSwap(neighborIndex);

            DungeonCell EndCell = NeighborEdge.GetEndCell();

            if (!Processed.Contains(EndCell)) {
                Edges.Add(NeighborEdge);
                CellStack.Push(EndCell);
                SeenStack.Push(NeighborEdge.GetHomeCell());
                break;
            }
            else if (FMath::FRand() < CycleProbability) {
                Edges.Add(NeighborEdge);
            }
        }

        Processed.Add(CurrentCell);
    }

}



/* ==================================
        Helper Functions 
=====================================*/

int32 DungeonSector::GetIndex(int32 x, int32 y) const
{
    return x + lengthX * y;
}

bool DungeonSector::Contains(const DungeonCell& Cell) const
{
    return Cell.x >= originX && Cell.x < (originX + lengthX) && Cell.y >= originY && Cell.y < (originY + lengthY);
}

bool DungeonSector::Validate(const DungeonCellEdge &Edge) const
{
    switch (Edge.Direction) {
        case EEdgeDirection::XPlus:
            return Edge.x < (lengthX - 1);
        case EEdgeDirection::XMinus:
            return Edge.x > 0;
        case EEdgeDirection::YPlus:
            return Edge.y < (lengthY - 1);
        case EEdgeDirection::YMinus:
            return Edge.y > 0;
    }
    return false;
}

bool DungeonSector::Validate(const DungeonCell &Cell) const
{
    return Cell.x >= 0 && Cell.x < lengthX && Cell.y > 0 && Cell.y < lengthY;
}

TArray<DungeonCellEdge> DungeonSector::GetNeighborEdges(const DungeonCell &Cell)
{
    TArray<DungeonCellEdge> Neighbors;

    int32 x = Cell.x;
    int32 y = Cell.y;

    if (x > 0) {
        Neighbors.Add(DungeonCellEdge(x, y, EEdgeDirection::XMinus));
    }
    if (x < (lengthX - 1)) {
        Neighbors.Add(DungeonCellEdge(x, y, EEdgeDirection::XPlus));
    }
    if (y > 0) {
        Neighbors.Add(DungeonCellEdge(x, y, EEdgeDirection::YMinus));
    }
    if (y < (lengthY - 1)) {
        Neighbors.Add(DungeonCellEdge(x, y, EEdgeDirection::YPlus));
    }

    return Neighbors;
}