// Fill out your copyright notice in the Description page of Project Settings.


#include "CBoxBase.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ACBoxBase::ACBoxBase()
{
	RootSceneComp = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	RootComponent = RootSceneComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	BoxComp->SetupAttachment(RootSceneComp);
	BoxComp->SetRelativeScale3D(FVector(3));
	BoxComp->bHiddenInGame = false;

	TextRenderComp = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComp");
	TextRenderComp->SetupAttachment(RootSceneComp);
	TextRenderComp->SetRelativeLocation(FVector(0, 0, 100));
	TextRenderComp->SetRelativeRotation(FRotator(0, 180, 0));
	TextRenderComp->TextRenderColor = FColor::Red;
	TextRenderComp->HorizontalAlignment = EHTA_Center;
	
	// Blue Print GetDisplay Name
	TextRenderComp->Text = FText::FromString(GetName());
}

// Called when the game starts or when spawned
void ACBoxBase::BeginPlay()
{
	Super::BeginPlay();
}

