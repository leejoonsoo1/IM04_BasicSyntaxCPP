
#include "CStaticMeshActor.h"

ACStaticMeshActor::ACStaticMeshActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;
}

void ACStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACStaticMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

