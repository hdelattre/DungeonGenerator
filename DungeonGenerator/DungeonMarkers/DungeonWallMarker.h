// Copyright 2016-2017 Bazel Games

#pragma once

#include "DungeonStaticMeshMarker.h"
#include "DungeonFloorMarker.h"

/**
 * 
 */
class WIZZ_API DungeonWallMarker : public DungeonStaticMeshMarker
{
public:
	DungeonWallMarker();
	~DungeonWallMarker();

    DungeonWallMarker(const FVector &Location, const FRotator &Rotation);

    virtual bool UseInMinimap() const override;

    virtual FTransform GetNormalizedTransform(float cellSize) const override;

    virtual const FName GetFolderString() const override;

private:

    virtual UStaticMesh* GetMeshFromTheme() override;

    virtual FVector GetMeshPivot() const override;
};
