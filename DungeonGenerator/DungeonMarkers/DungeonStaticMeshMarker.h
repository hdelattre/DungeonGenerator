// Copyright 2016-2017 Bazel Games

#pragma once

#include "DungeonObjectMarker.h"

/**
 * 
 */
class WIZZ_API DungeonStaticMeshMarker : public DungeonObjectMarker
{
public:

    UStaticMesh* ObjectMesh = nullptr;

    FVector PivotOffset;

    virtual bool SetTheme(UDungeonTheme *Theme) override;

    void SetMesh(UStaticMesh *Mesh);

    virtual FTransform GetNormalizedTransform(float cellSize) const override;

	DungeonStaticMeshMarker();
    DungeonStaticMeshMarker(const FVector &Location, const FRotator &Rotation);
	~DungeonStaticMeshMarker();

private:

    virtual UStaticMesh* GetMeshFromTheme();

    virtual FVector GetMeshPivot() const;
};
