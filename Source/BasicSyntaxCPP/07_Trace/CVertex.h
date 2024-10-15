#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CVertex.generated.h"

UCLASS()
class BASICSYNTAXCPP_API ACVertex : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACVertex();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* RootSceneComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

};
