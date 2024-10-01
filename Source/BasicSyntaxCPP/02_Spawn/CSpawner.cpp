// Fill out your copyright notice in the Description page of Project Settings.

#include "CSpawner.h"
#include "CStaticMeshActor.h"

// Sets default values
ACSpawner::ACSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

}

// Called when the game starts or when spawned
void ACSpawner::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < (int32)EStaticMeshAssetType::Max; i++)
	{
		FTransform TM;

		StaticMeshBased[i] = GetWorld()->SpawnActor<ACStaticMeshActor>(StaticMeshBasedActorBasedClasses[i], TM);
		
		FVector Location = GetActorLocation();
		StaticMeshBased[i]->SetActorLocation(FVector(Location.X, Location.Y + 200 * i, Location.Z));
	}
}