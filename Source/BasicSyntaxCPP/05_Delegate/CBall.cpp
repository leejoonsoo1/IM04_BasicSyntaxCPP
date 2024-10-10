#include "CBall.h"

// Sets default values
ACBall::ACBall()
{
	RootSceneComp = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	RootComponent = RootSceneComp;

	for (int32 i = 0; i < 3; i++)
	{
		FString SubObjectName;
		SubObjectName.Append("MeshComp");
		SubObjectName.Append(FString::FromInt(i + 1));

		MeshComps[i] = CreateDefaultSubobject<USceneComponent>(FName(SubObjectName));
		MeshComps[i]->
	}
}

// Called when the game starts or when spawned
void ACBall::BeginPlay()
{
	Super::BeginPlay();
	
}