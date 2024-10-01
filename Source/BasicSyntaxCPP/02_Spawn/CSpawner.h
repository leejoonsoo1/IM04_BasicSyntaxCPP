// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpawner.generated.h"

class ACStaticMeshActor;

UENUM(BlueprintType)
enum class EStaticMeshAssetType : uint8
{
	Cube, Cone, Cylinder, Sphere, Max
};

UCLASS()
class BASICSYNTAXCPP_API ACSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	UClass* ObjectBasedClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACStaticMeshActor> StaticMeshBasedActorBasedClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACStaticMeshActor> StaticMeshBasedActorBasedClasses[(int32)EStaticMeshAssetType::Max];

private:
	ACStaticMeshActor* StaticMeshBased[(int32)EStaticMeshAssetType::Max];
};
