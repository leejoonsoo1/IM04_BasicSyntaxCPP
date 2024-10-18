#include "CAR4.h"
#include "BasicSyntaxCpp.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

ACAR4::ACAR4()
{
	PrimaryActorTick.bCanEverTick	= true;

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp");
	
	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Weapons/Meshes/AR4/SK_AR4");
	MeshComp->SetSkeletalMesh(MeshAsset);

	CHelpers::GetAsset(&EquipMontage, "/Game/Character/Animations/AR4/Rifle_Grab_Montage");
	CHelpers::GetAsset(&UnEquipMontage, "/Game/Character/Animations/AR4/Rifle_UnGrab_Montage");

	HolsterSocket	= "Holster_AR4";
	HandSocket		= "Hand_AR4";
}

void ACAR4::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	if (OwnerCharacter)
	{
		AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
	}
}

void ACAR4::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACAR4::Equip()
{
	if (bEquipped) return;
	if (bPlayingMontage) return;
		
	bPlayingMontage = true;
	OwnerCharacter->PlayAnimMontage(EquipMontage);
}

void ACAR4::Begin_Equip()
{
	bEquipped = true;
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
}

void ACAR4::End_Equip()
{
	bPlayingMontage = false;
}

void ACAR4::UnEquip()
{
	if (!bEquipped) return;
	if (bPlayingMontage) return;

	bPlayingMontage = true;
	OwnerCharacter->PlayAnimMontage(UnEquipMontage);
}

void ACAR4::Begin_UnEquip()
{
}

void ACAR4::End_UnEquip()
{
}