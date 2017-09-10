// Copyright 2016-2017 Bazel Games

#pragma once

#include "DungeonObjectMarker.h"

/**
 * 
 */
class WIZZ_API DungeonMinimapIndicatorMarker : public DungeonObjectMarker
{
public:
    
    AActor* IndicatedActor = nullptr;

	DungeonMinimapIndicatorMarker();
    DungeonMinimapIndicatorMarker(AActor* Indicated, float dungeonCellSize, float displayCellSize);
	~DungeonMinimapIndicatorMarker();

    virtual bool UseInMinimap() const override;

    virtual UClass* GetObjectTemplate() const override;

    virtual void UpdateTransform(float displayCellSize);

protected:

    float indicatedCellSize;

};
