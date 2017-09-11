// Copyright 2016-2017 Hunter Delattre

#include "Wizz.h"
#include "DungeonTheme.h"

UDungeonTheme::UDungeonTheme()
{
}

UDungeonTheme::~UDungeonTheme()
{
}

UStaticMesh* UDungeonTheme::GetRandomMesh(const TArray<FLootTableEntry> &Table) const
{
    float totalProbability = 0;

    for (FLootTableEntry Entry : Table) {
        totalProbability += Entry.probabilityWeight;
    }
    
    float rolledProbability = FMath::FRand();
    float cumulativeProbability = 0;

    for (FLootTableEntry Entry : Table) {
        cumulativeProbability += Entry.probabilityWeight;

        if (rolledProbability <= (cumulativeProbability / totalProbability)) {
            return Cast<UStaticMesh>(Entry.Mesh);
        }
    }

    return nullptr;
}