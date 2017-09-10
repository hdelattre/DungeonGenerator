// Copyright 2016-2017 Bazel Games

#pragma once

#include "GameFramework/Pawn.h"
#include "DungeonGenerator/DungeonGenerator.h"
#include "DungeonGenerator/DungeonFunctions.h"
#include "DungeonPawn.generated.h"

UCLASS(Blueprintable)
class WIZZ_API ADungeonPawn : public APawn
{
	GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "References")
    ADungeonGenerator* Dungeon;

	// Sets default values for this pawn's properties
	ADungeonPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    UFUNCTION(BlueprintCallable, Category = "Pathing")
    TArray<FVector> GetPathToLocation(FVector WorldLocation) const;


private:

    int32 CurrentMana;
    int32 MaxMana;

    int32 CurrentMovement;
    int32 MaxMovement;
};
