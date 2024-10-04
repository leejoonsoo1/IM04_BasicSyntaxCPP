// Fill out your copyright notice in the Description page of Project Settings.


#include "CDrawDebug.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACDrawDebug::ACDrawDebug()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TargetLocations1 = FVector(0, 0, 0);
	TargetLocations2 = FVector(100 + 500, 0, 0);

	TargetLocations3 = FVector(0, 100 + 250, 0);
	TargetLocations4 = FVector(100 + 500, 100 + 250, 0);

	TargetLocations5 = FVector(0, 100 + 500, 0);
	TargetLocations6 = FVector(100 + 500, 100 + 500, 0);
}

// Called when the game starts or when spawned
void ACDrawDebug::BeginPlay()
{
	Super::BeginPlay();

	FVector WorldLocation = GetActorLocation() + TargetLocations1;
	Box = FBox(FVector(-50, -100, -50), FVector(+50, +100, +50));

	DrawDebugBox(GetWorld(), WorldLocation + Box.GetCenter(), Box.GetExtent(), FColor::Orange, true);
	
}

// Called every frame
void ACDrawDebug::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WorldLocations[0] = GetActorLocation() + TargetLocations1;
	WorldLocations[1] = GetActorLocation() + TargetLocations2;
	WorldLocations[2] = GetActorLocation() + TargetLocations3;
	WorldLocations[3] = GetActorLocation() + TargetLocations4;
	WorldLocations[4] = GetActorLocation() + TargetLocations5;
	WorldLocations[5] = GetActorLocation() + TargetLocations6;

	DrawDebugSolidBox(GetWorld(), WorldLocations[1] + Box.GetCenter(), Box.GetExtent(), FColor::Purple);
	DrawDebugPoint(GetWorld(), WorldLocations[2], 30.f, FColor::Magenta);
	DrawDebugSphere(GetWorld(), WorldLocations[3], 100, 30, FColor::Emerald);
	DrawDebugCircle(GetWorld(), WorldLocations[4], 100, 30, FColor::Cyan);
	//DrawDebugString(GetWorld(), WorldLocations[5], GetName(), nullptr, FColor::Magenta);

	FVector ArrowStart = WorldLocations[1];
	FVector ArrowEnd = WorldLocations[4];
	
	DrawDebugDirectionalArrow(GetWorld(), ArrowStart, ArrowEnd, 200, FColor::Black, false, -1, 0, 10);
}

