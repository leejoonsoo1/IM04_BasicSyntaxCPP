#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStaticMeshActor.generated.h"

UCLASS()
class BASICSYNTAXCPP_API ACStaticMeshActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACStaticMeshActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void ChangeColor();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

private:
	UMaterialInstanceDynamic* DynamicMaterial;
};
