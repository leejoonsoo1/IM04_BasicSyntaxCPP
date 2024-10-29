#include "CAR4.h"
#include "BasicSyntaxCpp.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/DecalComponent.h"
#include "DrawDebugHelpers.h"
#include "particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "CWeaponInterface.h"
#include "CBullet.h"
#include "CMagazine.h"

static TAutoConsoleVariable<bool> CVarDrawDebugLine(TEXT("IM.DrawDebug"), false, TEXT("Visible AR4 aim line"), ECVF_Cheat);

ACAR4::ACAR4()
{
	PrimaryActorTick.bCanEverTick	= true;

	CHelpers::CreateSceneComponent(this, &MeshComp, "MeshComp");
	
	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset,		"/Game/Weapons/Meshes/AR4/SK_AR4");
	MeshComp->SetSkeletalMesh(MeshAsset);

	CHelpers::GetAsset(&EquipMontage,	"/Game/Character/Animations/AR4/Rifle_Grab_Montage");
	CHelpers::GetAsset(&UnEquipMontage, "/Game/Character/Animations/AR4/Rifle_UnGrab_Montage");
	CHelpers::GetAsset(&ReLoadMontage,	"/Game/Character/Animations/AR4/Rifle_Jog_Reload_Montage");

	CHelpers::GetClass(&ShakeClass,		"/Game/AR4/Shake_Fire");
	CHelpers::GetClass(&BulletClass,	"/Game/AR4/BP_CBullet");
	CHelpers::GetClass(&MagazineClass,	"/Game/AR4/BP_CMagaine");

	CHelpers::GetAsset(&MuzzleEffect,	"/Game/Particles_Rifle/Particles/VFX_Muzzleflash");
	CHelpers::GetAsset(&EjectEffect,	"/Game/Particles_Rifle/Particles/VFX_Eject_bullet");
	CHelpers::GetAsset(&ImpactEffect,	"/Game/Particles_Rifle/Particles/VFX_Impact_Default");
	CHelpers::GetAsset(&FireSound,		"/Game/Sounds/S_RifleShoot_Cue");
	CHelpers::GetAsset(&DecalMaterial,	"/Game/Materials/M_Decal");

	HolsterSocket = "Holster_AR4";
	HandSocket = "Hand_AR4";
	MontagePlayRate = 1.75f;
	ShootRange = 10000.f;
	CurrentAmmo = 30;
	PitchSpeed = 0.25f;
	MagazineSize = 30;
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

void ACAR4::ToggleAutoFiring()
{
	bAutoFiring = !bAutoFiring;
}

void ACAR4::EnableAim()
{
	bAiming = true;
}

void ACAR4::DisableAim()
{ 
	bAiming = false; 
	GetWorld()->GetTimerManager().ClearTimer(AutoFireTimer);
}

void ACAR4::Equip()
{
	if (bEquipped) return;
	if (bPlayingMontage) return;
	if (bReload) return;

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
	if (bReload) return;

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

void ACAR4::SpawnMag(FName Socket)
{
	FVector		Loc = OwnerCharacter->GetMesh()->GetSocketLocation(Socket);
	FRotator	Rot = OwnerCharacter->GetMesh()->GetSocketRotation(Socket);
	
	Mag = GetWorld()->SpawnActor<ACMagazine>(MagazineClass, Loc, Rot);
	
	if (Mag)
	{
		MagComp = Mag->GetMesh();
		
		if (MagComp)
		{
			Mag->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
		}
	}
}

void ACAR4::ThrowMag(FVector Location, FRotator Rotation)
{
	if (MagComp)
	{
		MagComp->SetSimulatePhysics(true);
		Mag->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		// 위치와 회전 정보를 기반으로 던질 방향 계산
		FVector ThrowDirection = Rotation.Vector(); // 회전에서 방향 벡터 얻기

		// 힘의 크기 설정 (조정 가능)
		float ThrowForceMagnitude = 100.0f;

		// 힘을 계산
		FVector ForceToAdd = ThrowDirection * ThrowForceMagnitude;

		// 매거진의 메쉬 컴포넌트에 힘 추가
		MagComp->AddImpulse(ForceToAdd, NAME_None, true);

		// 매거진의 위치를 던질 위치로 설정
		Mag->SetActorLocation(Location);
	}
}

void ACAR4::DestroyMag()
{
	if (Mag)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimeHandle);
		Mag->Destroy();
	}
}

void ACAR4::OnFire()
{
	if (!bEquipped) return;
	if(bPlayingMontage) return;

	if (!bAiming) return;
	if (bFiring) return;
	if (bReload) return;

	if (bAutoFiring)
	{
		GetWorld()->GetTimerManager().SetTimer(AutoFireTimer, this, &ACAR4::Firing_Internal, 0.1f, true, 0.f);

		return;
	}

	bFiring = true;

	CurrentPitch = 0.f;

	Firing_Internal();
}

void ACAR4::OffFire()
{
	bFiring = false;

	if (bAutoFiring)
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoFireTimer);
	}
}

void ACAR4::Begin_Reload()
{
	bReload = true;
	bFiring = false;
	bPlayingMontage = true;
	
	GetWorld()->GetTimerManager().ClearTimer(AutoFireTimer);
}

void ACAR4::End_Reload()
{
	bReload = false;
	bPlayingMontage = false;
	CurrentAmmo = 30;
}

void ACAR4::Reload()
{
	if (!bEquipped || bPlayingMontage) return;

	OwnerCharacter->PlayAnimMontage(ReLoadMontage, MontagePlayRate);
}

void ACAR4::Firing_Internal()
{
	// Get Aim Ray
	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(OwnerCharacter);
	if (!OwnerInterface) return;

	FVector Start, End, Direction;
	OwnerInterface->GetAimRay(Start, End, Direction);

	// Camera Shake
	if (!OwnerCharacter) return;

	APlayerController* PC = OwnerCharacter->GetController<APlayerController>();

	if (PC)
	{
		PC->PlayerCameraManager->PlayCameraShake(ShakeClass);
	}

	// Spawn Bullet
	FVector MuzzleLocation = MeshComp->GetSocketLocation("MuzzleFlash");
	if (BulletClass)
	{
		GetWorld()->SpawnActor<ACBullet>(BulletClass, MuzzleLocation, Direction.Rotation());
		CurrentAmmo--;

		if (CurrentAmmo == 0)
		{
			Reload();
		}
	}

	// Play Effect
	UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, "MuzzleFlash");
	UGameplayStatics::SpawnEmitterAttached(EjectEffect, MeshComp, "EjectBullet");
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, MuzzleLocation);

	// LineTrace for Visibility
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(OwnerCharacter);

	// Increase Pitch
	CurrentPitch -= PitchSpeed * GetWorld()->GetDeltaSeconds();
	
	if (CurrentPitch > -PitchSpeed)
	{
		OwnerCharacter->AddControllerPitchInput(CurrentPitch);
	}
	
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, QueryParams))
	{
		FRotator ImpactRotation = Hit.ImpactNormal.Rotation();

		// Spawn Decal
		UDecalComponent* DecalComp = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMaterial, FVector(5, 5, 5), Hit.ImpactPoint, ImpactRotation, 3.f);
		DecalComp->SetFadeScreenSize(0.f);

		// Play Impact
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.ImpactPoint, ImpactRotation);

		// Add Impulse about PhysicsBody
		UPrimitiveComponent* HitComp = Hit.GetComponent();
		if (Hit.GetComponent()->IsSimulatingPhysics())
		{
			Direction = Hit.GetActor()->GetActorLocation() - OwnerCharacter->GetActorLocation();
			Direction.Normalize();
			HitComp->AddImpulseAtLocation(Direction * 30000.f, OwnerCharacter->GetActorLocation());
		}
	}
}

int ACAR4::GetCurrentAmmo()
{
	return CurrentAmmo;
}