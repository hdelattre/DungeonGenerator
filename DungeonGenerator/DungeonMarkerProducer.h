// Copyright 2016-2017 Hunter Delattre

#pragma once

#include "DungeonSector.h"
#include "DungeonFunctions.h"

#include "DungeonMarkers/DungeonFloorMarker.h"
#include "DungeonMarkers/DungeonWallMarker.h"
#include "DungeonMarkers/DungeonPillarMarker.h"

#include "DungeonMarkers/DungeonMinimapIndicatorMarker.h"
#include "DungeonMarkers/DungeonPlayerIndicatorMarker.h"
#include "DungeonMarkers/DungeonFloorHighlighterMarker.h"

/**
 * 
 */
class WIZZ_API DungeonMarkerProducer
{
public:
    DungeonMarkerProducer();
	~DungeonMarkerProducer();

    static TArray<DungeonStaticMeshMarker*> CreateSectorArchitectureMarkers(const DungeonSector& Sector);

    static TArray<DungeonObjectMarker*> CreateSectorMarkers(const DungeonSector& Sector);


};
