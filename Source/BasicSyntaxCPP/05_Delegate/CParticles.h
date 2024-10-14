// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CParticles.generated.h"

class UParticleSystem;
class UTextRenderComponent;


UCLASS()
class BASICSYNTAXCPP_API ACParticles : public AActor
{
	GENERATED_BODY()
	
public:	
	ACParticles();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void SpawnEmitter(int32 InIndex);

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* RootSceneComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UTextRenderComponent* TextRenderComp;


	UPROPERTY(VisibleInstanceOnly)
	UParticleSystem* Particles[3];




};
