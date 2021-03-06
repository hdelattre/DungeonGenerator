// Copyright 2016-2017 Hunter Delattre

#pragma once

#include "DungeonStaticMeshMarker.h"
#include "DungeonFloorMarker.h"

/**
 * 
 */
class WIZZ_API DungeonPillarMarker : public DungeonStaticMeshMarker
{
public:
	DungeonPillarMarker();
	~DungeonPillarMarker();

    DungeonPillarMarker(const FVector &Location, const FRotator &Rotation);

    virtual bool UseInMinimap() const override;

    virtual FTransform GetNormalizedTransform(float cellSize) const override;

    virtual const FName GetFolderString() const override;

private:

    virtual UStaticMesh* GetMeshFromTheme() override;

    virtual FVector GetMeshPivot() const override;

};
