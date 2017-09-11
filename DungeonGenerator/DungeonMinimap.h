// Copyright 2016-2017 Hunter Delattre

#pragma once

#include "GameFramework/Actor.h"
#include "DungeonGenerator.h"
#include "DungeonMinimap.generated.h"

UCLASS()
class WIZZ_API ADungeonMinimap : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	

    UDungeonTheme* Theme = nullptr;

    TMap<UStaticMesh*, UInstancedStaticMeshComponent*> MinimapMeshInstances;

	// Sets default values for this actor's properties
    ADungeonMinimap();

    ~ADungeonMinimap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Setup(ADungeonGenerator* Dungeon, UDungeonTheme* Theme, const FVector& Bounds);

    UFUNCTION(BlueprintCallable, Category = "Indicators")
    AActor* CreateIndicatorForActor(AActor* IndicatedActor);

    UFUNCTION(BlueprintCallable, Category = "Indicators")
    AActor* CreateRotationalIndicatorForActor(AActor* IndicatedActor, USceneComponent* RotationComponent = nullptr);

	
private:

    // The sector that will be displayed by the minimap
    UPROPERTY()
    ADungeonGenerator* MappedDungeon = nullptr;

    // This minimap's cell size (will be determined automatically to fit within bounds)
    float minimapCellSize = 0;

    UPROPERTY()
    USceneComponent* SpawnRoot;

    TArray<DungeonMinimapIndicatorMarker*> Indicators;

    // The extent of the minimap in the positive x and y directions from the origin
    FVector DisplayBounds;

    // How far the current minimap position was adjusted to properly fit within the specified bounds
    FVector PositionAdjustment;

    AActor* ReadMarkerForActor(DungeonObjectMarker *Marker);

    void ConsumeMarkerForMesh(DungeonStaticMeshMarker *Marker);

    void UpdateIndicator(DungeonMinimapIndicatorMarker* IndicatorMarker);

    void CreateArchitecture();

};
