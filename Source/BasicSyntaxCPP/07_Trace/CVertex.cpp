#include "CVertex.h"
#include "BasicSyntaxCpp.h"

ACVertex::ACVertex()
{
	CHelpers::CreateSceneComponent(this, &RootSceneComp, "RootScene");
	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp", RootSceneComp);
	 
	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/StaticMeshes/SM_Sphere");
	MeshComp->SetStaticMesh(MeshAsset);

	UMaterial* MaterialAsset;
	CHelpers::GetAsset(&MaterialAsset, "/Game/StaticMeshes/M_Emissive");
	MeshComp->SetMaterial(0, MaterialAsset);
}

void ACVertex::BeginPlay()
{
	Super::BeginPlay();
	
}


