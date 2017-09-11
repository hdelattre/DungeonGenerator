// Copyright 2016-2017 Hunter Delattre

#pragma once

#include "GameFramework/Actor.h"
#include "DungeonFunctions.h"
#include "DungeonMarkerProducer.h"
#include "DungeonTheme.h"
#include "DungeonGenerator.generated.h"

UCLASS()
class WIZZ_API ADungeonGenerator : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Theme")
    UDungeonTheme* DungeonTheme;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gen Parameters", Meta = (ClampMin = 0))
    int32 LayoutSeed = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gen Parameters", Meta = (ClampMin = 1))
    float cellSize = 300;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gen Parameters", Meta = (ClampMin = 1, ClampMax = 200))
    int32 SectorXLength = 5;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gen Parameters", Meta = (ClampMin = 1, ClampMax = 200))
    int32 SectorYLength = 5;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gen Parameters", Meta = (ClampMin = 0, ClampMax = 1))
    float CycleProbability = .05;

	// Sets default values for this actor's properties
	ADungeonGenerator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UFUNCTION(BlueprintCallable, Category = "Pathing")
    FVector GetCellCenter(FVector Location) const;

    UFUNCTION(BlueprintCallable, Category = "Pathing")
    TArray<FVector> GetCellPath(FVector StartLocation, FVector EndLocation) const;

    DungeonSector* GetCurrentSector() const;



    // Marker Spawning

    AActor* ReadMarkerForActor(DungeonObjectMarker *Marker, AActor* Outer);

    void ConsumeMarkerForMesh(DungeonStaticMeshMarker* Marker, AActor* Outer);

    AActor* ConsumeMarkerForActor(DungeonObjectMarker* Marker, AActor* Outer);


private:

    TArray<DungeonSector> Sectors;

    DungeonSector* CurrentSector;

    TMap<UStaticMesh*, UInstancedStaticMeshComponent*> DungeonMeshInstances;

    // Generation Functions
    void BuildDungeon();

    void GenerateSectors();

    void SpawnSector(const DungeonSector &Sector);


    

    // Helper Functions
    

};
