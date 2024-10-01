// Fill out your copyright notice in the Description page of Project Settings.


#include "CStaticMeshActor_Sphere.h"

ACStaticMeshActor_Sphere::ACStaticMeshActor_Sphere()
{
	// Full Ref Path : "StaticMesh'/Game/StaticMeshes/SM_Sphere.SM_Sphere'"
	// Alias Ref Path : "/Game/StaticMeshes/SM_Sphere"

	ConstructorHelpers::FObjectFinder<UStaticMesh> SMAsset(TEXT("/Game/StaticMeshes/SM_Sphere"));
	
	if (SMAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(SMAsset.Object);
	}
}

