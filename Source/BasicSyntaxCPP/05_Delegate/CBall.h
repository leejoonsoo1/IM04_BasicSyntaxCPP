#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBall.generated.h"

UCLASS()
class BASICSYNTAXCPP_API ACBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* RootSceneComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComps[3];


};
