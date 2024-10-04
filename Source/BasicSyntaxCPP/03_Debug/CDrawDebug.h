// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDrawDebug.generated.h"

UCLASS()
class BASICSYNTAXCPP_API ACDrawDebug : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACDrawDebug();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
	FVector TargetLocations1;
	
	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
	FVector TargetLocations2;
	
	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
	FVector TargetLocations3;
	
	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
	FVector TargetLocations4;
	
	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
	FVector TargetLocations5;

	UPROPERTY(EditAnywhere, Category = "DrawDebug", meta = (MakeEditWidget))
	FVector TargetLocations6;

	FBox Box;
	FVector WorldLocations[6];
};
