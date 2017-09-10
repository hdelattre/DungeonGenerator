// Copyright 2016-2017 Bazel Games

#include "Wizz.h"
#include "DungeonPawn.h"


// Sets default values
ADungeonPawn::ADungeonPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADungeonPawn::BeginPlay()
{
	Super::BeginPlay();
	
    for (TActorIterator<ADungeonGenerator> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        Dungeon = *ActorItr;
    }
}

// Called every frame
void ADungeonPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADungeonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


TArray<FVector> ADungeonPawn::GetPathToLocation(FVector WorldLocation) const
{
    return DungeonFunctions::GetCellPathLocations(GetActorLocation(), WorldLocation, Dungeon->cellSize, *(Dungeon->GetCurrentSector()));
}