// Fill out your copyright notice in the Description page of Project Settings.


#include "CStaticMeshActor_Cylinder.h"

ACStaticMeshActor_Cylinder::ACStaticMeshActor_Cylinder()
{
	// Full Ref Path : "StaticMesh'/Game/StaticMeshes/SM_Sphere.SM_Sphere'"
	// Alias Ref Path : "/Game/StaticMeshes/SM_Sphere"

	ConstructorHelpers::FObjectFinder<UStaticMesh> SMAsset(TEXT("/Game/StaticMeshes/SM_Sphere"));
	
	if (SMAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(SMAsset.Object);
	}
}

