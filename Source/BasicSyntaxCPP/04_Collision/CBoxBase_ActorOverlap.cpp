// Fill out your copyright notice in the Description page of Project Settings.

#include "CBoxBase_ActorOverlap.h"
#include "Utilities/CLog.h"

void ACBoxBase_ActorOverlap::BeginPlay()
{
	Super::BeginPlay();

	// 함수 소요한 객체의 주소, &함수의 주소
	OnActorBeginOverlap.AddDynamic(this, &ACBoxBase_ActorOverlap::BeginOverlap);
}

void ACBoxBase_ActorOverlap::BeginOverlap(AActor* OverlappedActor /*나*/, AActor* OtherActor /*박은놈*/)
{
	PrintLine();

	CLog::Print(OtherActor->GetName() + " is overlapped");
}
