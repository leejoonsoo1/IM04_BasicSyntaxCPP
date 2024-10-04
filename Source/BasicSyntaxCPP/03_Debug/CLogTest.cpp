// Fill out your copyright notice in the Description page of Project Settings.


#include "CLogTest.h"
#include "Utilities/CLog.h"

// Sets default values
ACLogTest::ACLogTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACLogTest::BeginPlay()
{
	Super::BeginPlay();

	CLog::Print(1);
	CLog::Print(2, 1);
	CLog::Print(3, 2, 10.f);
	CLog::Print(4, 2, 10.f, FColor::Red);
	CLog::Print("Test");
	CLog::Print(GetActorLocation());
	CLog::Print(GetActorRotation());

	CLog::Log(20);
	CLog::Log(PI);
	CLog::Log("Log Test");
	CLog::Log(GetActorLocation());
	CLog::Log(GetActorRotation());
	CLog::Log(this);
	CLog::Log(__FILE__);
	PrintLine();
	CLog::Log(GetClass()->GetName());
}

// Called every frame
void ACLogTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	CLog::Print(GetWorld()->TimeSeconds, 500, 2.f, FColor::Green);

}

