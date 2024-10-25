#include "CAR4.h"
#include "BasicSyntaxCpp.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "CWeaponInterface.h"

static TAutoConsoleVariable<bool> CVarDrawDebugLine(TEXT("IM.DrawDebug"), false, TEXT("Visible AR4 aim line"), ECVF_Cheat);

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
	MontagePlayRate = 1.75f;
	ShootRange		= 10000.f;
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

	if (!bAiming) return;

	// LineTrace
	// Start, End 
	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(OwnerCharacter);
	if (!OwnerInterface) return;

	FVector Start, End, Direction;
	OwnerInterface->GetAimRay(Start, End, Direction);

	if (CVarDrawDebugLine.GetValueOnGameThread())
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1.0f, (uint8)0U, 3.f);
	}

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(OwnerCharacter);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_PhysicsBody, QueryParams))
	{
		if (Hit.GetComponent()->IsSimulatingPhysics())
		{
			OwnerInterface->OnTarget();

			return;
		}
	}

	OwnerInterface->OffTarget();
}

void ACAR4::EnableAim()
{
	bAiming = true;
}

void ACAR4::DisableAim()
{ 
	bAiming = false; 
}

void ACAR4::Equip()
{
	if (bEquipped) return;
	if (bPlayingMontage) return;
		
	bPlayingMontage = true;
	OwnerCharacter->PlayAnimMontage(EquipMontage, MontagePlayRate);
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
	OwnerCharacter->PlayAnimMontage(UnEquipMontage, MontagePlayRate);
}

void ACAR4::Begin_UnEquip()
{
	bEquipped = false;

	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HolsterSocket);
}

void ACAR4::End_UnEquip()
{
	bPlayingMontage = false;
}

void ACAR4::OnFire()
{
	if (!bEquipped) return;
	if (bPlayingMontage) return;

	if (!bAiming) return;
	if (bFiring) return;

	bFiring = true;

	Firing_Internal();
}

void ACAR4::OffFire()
{
	bFiring = false;
}

void ACAR4::Firing_Internal()
{
	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(OwnerCharacter);
	if (!OwnerInterface) return;

	FVector Start, End, Direction;
	OwnerInterface->GetAimRay(Start, End, Direction);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(OwnerCharacter);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, QueryParams))
	{
		// Add Impulse about PhysicsBody
		UPrimitiveComponent* HitComp = Hit.GetComponent();
		if (Hit.GetComponent()->IsSimulatingPhysics())
		{
			//Direction = Hit.GetActor()->GetActorLocation() - OwnerCharacter->GetActorLocation();
			Direction.Normalize();

			HitComp->AddImpulseAtLocation(Direction * 30000.f, OwnerCharacter->GetActorLocation());
		}
	}
}
