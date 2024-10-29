#include "CMagazine.h"
#include "BasicSyntaxCpp.h"
#include "Components\StaticMeshComponent.h"
#include "GameFramework\Character.h"

ACMagazine::ACMagazine()
{
	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp");

	UStaticMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Weapons/Meshes/Magazine/SM_AR4_Mag_Empty");
	MeshComp->SetStaticMesh(MeshAsset);
	MeshComp->SetCollisionProfileName("Custom");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACMagazine::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(5);
}