// Copyright 2016-2017 Bazel Games

#pragma once

#include "DungeonSector.h"

static const float PATHING_BIAS_CENTER_ANGLE = .05;

enum class EDungeonPathBias : uint8
{
    Left,
    CenterLeft,
    CenterRight,
    Right
};

const TArray<EEdgeDirection> DEFAULT_EDGE_ORDER = {
    EEdgeDirection::XPlus,
    EEdgeDirection::YPlus,
    EEdgeDirection::XMinus,
    EEdgeDirection::YMinus
};

/**
 * 
 */
class WIZZ_API DungeonFunctions
{
public:

    struct DungeonPathParams
    {
        DungeonCell StartCell;
        DungeonCell EndCell;
        EDungeonPathBias Bias;

        DungeonPathParams() {};
        DungeonPathParams(const DungeonCell& Start, const DungeonCell& End, const EDungeonPathBias& PathBias)
            : StartCell(Start), EndCell(End), Bias(PathBias) {};

        DungeonPathParams(const FVector& StartLocation, const FVector& EndLocation, float cellSize)
        {
            StartCell = DungeonCell(StartLocation, cellSize);
            EndCell = DungeonCell(EndLocation, cellSize);
            Bias = InferPathBias(StartLocation, EndLocation, cellSize);
        };

        friend bool operator!=(const DungeonPathParams& A, const DungeonPathParams& B)
        {
            return A.EndCell != B.EndCell || A.StartCell != B.StartCell || A.Bias != B.Bias;
        };
    };

	DungeonFunctions();
	~DungeonFunctions();

    static FVector WorldToCellLocation(const FVector& WorldLocation, float cellSize);

    static void WorldToCellLocation(const FVector& WorldLocation, float cellSize, int32& CellX, int32& CellY);

    static void WorldToCellLocation(const FVector& WorldLocation, float cellSize, float& CellX, float& CellY);

    static FVector CellToWorldLocation(const FVector& CellLocation, float cellSize);

    static FVector CellToWorldLocation(const DungeonCell& Cell, float cellSize);



    static TArray<DungeonCell> LocationsToCells(const TArray<FVector>& Locations, float cellSize);

    static TArray<FVector> CellsToLocations(const TArray<DungeonCell>& Cells, float cellSize);



    static TArray<DungeonCell> GetNeighborCells(const DungeonCell& Cell, const DungeonSector& Sector, const TArray<EEdgeDirection>& Order = DEFAULT_EDGE_ORDER);



    /*******************
    *     PATHING
    ********************/

    static TArray<DungeonCell> GetCellPath(DungeonCell StartCell, DungeonCell EndCell, const DungeonSector& Sector, const EDungeonPathBias& Bias);

    FORCEINLINE static TArray<DungeonCell> GetCellPath(const DungeonPathParams& PathParams, const DungeonSector& Sector)
    {
        return GetCellPath(PathParams.StartCell, PathParams.EndCell, Sector, PathParams.Bias);
    };

    FORCEINLINE static TArray<DungeonCell> GetCellPath(FVector StartLocation, FVector EndLocation, float cellSize, const DungeonSector& Sector, const EDungeonPathBias& Bias)
    {
        return GetCellPath(DungeonCell(StartLocation, cellSize), DungeonCell(EndLocation, cellSize), Sector, Bias);
    };

    // Get cell path with inferred bias
    FORCEINLINE static TArray<DungeonCell> GetCellPath(FVector StartLocation, FVector EndLocation, float cellSize, const DungeonSector& Sector)
    {
        return GetCellPath(StartLocation, EndLocation, cellSize, Sector, InferPathBias(StartLocation, EndLocation, cellSize));
    };

    FORCEINLINE static TArray<FVector> GetCellPathLocations(FVector StartLocation, FVector EndLocation, float cellSize, const DungeonSector& Sector, const EDungeonPathBias& Bias)
    {
        return CellsToLocations(GetCellPath(StartLocation, EndLocation, cellSize, Sector, Bias), cellSize);
    };


    // Get location path with inferred bias
    FORCEINLINE static TArray<FVector> GetCellPathLocations(FVector StartLocation, FVector EndLocation, float cellSize, const DungeonSector& Sector)
    {
        return GetCellPathLocations(StartLocation, EndLocation, cellSize, Sector, InferPathBias(StartLocation, EndLocation, cellSize));
    };

    static EDungeonPathBias InferPathBias(const FVector& StartLocation, const FVector& EndLocation, float cellSize);

private:

    static EEdgeDirection NumToEdgeDirection(uint8 direction);

    static TArray<EEdgeDirection> GetNeighborOrder(const DungeonCell& StartCell, const DungeonCell& EndCell, const EDungeonPathBias& Bias);

    
};

typedef DungeonFunctions::DungeonPathParams DungeonPathParams;