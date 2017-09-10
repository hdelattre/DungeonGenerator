// Copyright 2016-2017 Bazel Games

#pragma once

#include "DungeonObjectMarker.h"

/**
 * 
 */
class WIZZ_API DungeonFloorHighlighterMarker : public DungeonObjectMarker
{
public:

    AActor* SpawnedActor = nullptr;

    bool bInSelection = true;

	DungeonFloorHighlighterMarker();
    DungeonFloorHighlighterMarker(const FVector &Location, const FRotator &Rotation);
	~DungeonFloorHighlighterMarker();

    virtual UClass* GetObjectTemplate() const override;

    virtual bool UseInMinimap() const override;
};
