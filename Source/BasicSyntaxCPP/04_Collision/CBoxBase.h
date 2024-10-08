// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBoxBase.generated.h"

class UBoxComponent;
class UTextRenderComponent;

UCLASS()
class BASICSYNTAXCPP_API ACBoxBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACBoxBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	// TransForm�� ���� ��� ������Ʈ�� �θ�
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* RootSceneComp; // RootComponent

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UTextRenderComponent* TextRenderComp;
};
