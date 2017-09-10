// Copyright 2016-2017 Bazel Games

#pragma once

#include "DungeonTheme.generated.h"

UENUM(BlueprintType)
enum class EDungeonObjectType : uint8
{
    Floor UMETA(DisplayName = "Floor"),
    Wall UMETA(DisplayName = "Wall"),
    Prop UMETA(DisplayName = "Prop"),
    Objective UMETA(DisplayName = "Objective"),
    Item UMETA(DisplayName = "Item")
};

USTRUCT(BlueprintType)
struct FLootTableEntry
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    UStaticMesh* Mesh;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float probabilityWeight = 1.0f;
};

/**
 * 
 */
UCLASS(Blueprintable)
class WIZZ_API UDungeonTheme : public UDataAsset
{
public:

    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Architecture|Floor")
    TArray<FLootTableEntry> FloorMeshes;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Architecture|Wall")
    float WallHeight = 1.0f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Architecture|Wall")
    TArray<FLootTableEntry> WallMeshes;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Architecture|Pillar")
    float PillarSize = 1.0f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Architecture|Pillar")
    float PillarHeight = 1.0f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Architecture|Pillar")
    TArray<FLootTableEntry> PillarMeshes;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Interface Displays|Floor")
    TSubclassOf<AActor> FloorHighlighter;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Minimap|Indicators")
    TSubclassOf<AActor> PawnIndicator;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Minimap|Indicators")
    TSubclassOf<AActor> ObjectIndicator;

    // returns nullptr if Meshes is empty
    UStaticMesh* GetRandomMesh(const TArray<FLootTableEntry> &Table) const;

    UDungeonTheme();
	~UDungeonTheme();

};
