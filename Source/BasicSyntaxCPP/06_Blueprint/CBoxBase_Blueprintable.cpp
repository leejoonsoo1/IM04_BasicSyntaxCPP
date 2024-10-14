#include "CBoxBase_Blueprintable.h"

void ACBoxBase_Blueprintable::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACBoxBase_Blueprintable::BeginOverlap);
	OnActorBeginOverlap.AddDynamic(this, &ACBoxBase_Blueprintable::EndOverlap);
}

void ACBoxBase_Blueprintable::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

}

void ACBoxBase_Blueprintable::EndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

}