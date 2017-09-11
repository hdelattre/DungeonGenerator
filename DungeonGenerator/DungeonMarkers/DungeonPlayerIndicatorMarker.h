// Copyright 2016-2017 Hunter Delattre

#pragma once

#include "DungeonMinimapIndicatorMarker.h"

/**
 * 
 */
class WIZZ_API DungeonPlayerIndicatorMarker : public DungeonMinimapIndicatorMarker
{
public:

    USceneComponent* IndicatedRotComponent = nullptr;

    DungeonPlayerIndicatorMarker();
    DungeonPlayerIndicatorMarker(AActor* Indicated, USceneComponent* RotationComponent, float dungeonCellSize, float displayCellSize);
    ~DungeonPlayerIndicatorMarker();

    virtual UClass* GetObjectTemplate() const override;

    virtual void UpdateTransform(float displayCellSize) override;
};
