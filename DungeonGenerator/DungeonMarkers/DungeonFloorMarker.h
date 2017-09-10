// Copyright 2016-2017 Bazel Games

#pragma once

#include "DungeonStaticMeshMarker.h"

const float DUNGEON_FLOOR_THICKNESS = .5;

/**
 * 
 */
class WIZZ_API DungeonFloorMarker : public DungeonStaticMeshMarker
{
public:

	DungeonFloorMarker();
    DungeonFloorMarker(const FVector &Location, const FRotator &Rotation);
	~DungeonFloorMarker();

    virtual bool UseInMinimap() const override;

    virtual FTransform GetNormalizedTransform(float cellSize) const override;

    virtual const FName GetFolderString() const override;

private:

    virtual UStaticMesh* GetMeshFromTheme() override;

    virtual FVector GetMeshPivot() const override;
};
