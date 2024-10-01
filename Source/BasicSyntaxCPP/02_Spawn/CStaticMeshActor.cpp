#include "CStaticMeshActor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"

ACStaticMeshActor::ACStaticMeshActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;
}

void ACStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();

	StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("MaterialInstanceConstant'/Game/StaticMeshes/MI_StaticMesh.MI_StaticMesh'"));

	UMaterialInstanceDynamic::Create(,);
	
}

void ACStaticMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

