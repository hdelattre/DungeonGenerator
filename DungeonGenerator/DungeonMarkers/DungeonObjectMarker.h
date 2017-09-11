// Copyright 2016-2017 Hunter Delattre

#pragma once

#include "../DungeonFunctions.h"
#include "../DungeonTheme.h"

const float DUNGEON_ASSUMED_OBJECT_SCALE = 100.f;

/**
 * Represents a type and transform for a dungeon object to be spawned.
 */
class WIZZ_API DungeonObjectMarker
{
public:

    AActor* SpawnedActor = nullptr;

    FVector Location;
    FRotator Rotation;

    UDungeonTheme* Theme = nullptr;

	DungeonObjectMarker();
    DungeonObjectMarker(const FVector &Location, const FRotator &Rotation);
	~DungeonObjectMarker();

    virtual bool SetTheme(UDungeonTheme *Theme);

    virtual bool UseInMinimap() const;

    virtual UClass* GetObjectTemplate() const;

    virtual void SetupNewActor(AActor* NewActor) const;

    virtual FTransform GetNormalizedTransform(float cellSize) const;

    virtual const FName GetFolderString() const;

    FTransform GetTransform() const;
    FVector GetLocation() const;
    FRotator GetRotation() const;

private:

    
};
