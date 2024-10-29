#include "CAnimNotifyState_Throw_Magazine.h"
#include "Weapons/CWeaponInterface.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapons/CAR4.h"

void UCAnimNotifyState_Throw_Magazine::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
		
	OwnerCharacter = OwnerCharacter = Cast<ACharacter>(MeshComp->GetOwner());

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(MeshComp->GetOwner());

	Loc = OwnerCharacter->GetMesh()->GetSocketLocation("hand_Magazine");
	Rot = OwnerCharacter->GetMesh()->GetSocketRotation("hand_Magazine");

	if (OwnerInterface)
	{
		ACAR4* AR4 = OwnerInterface->GetWeapon();

		if (AR4)
		{
			AR4->GetMesh()->HideBoneByName("b_gun_mag", EPhysBodyOp::PBO_Term);
			AR4->SpawnMag("hand_Magazine");
		}
	}	
}


void UCAnimNotifyState_Throw_Magazine::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(MeshComp->GetOwner());

	if (OwnerInterface)
	{
		ACAR4* AR4 = OwnerInterface->GetWeapon();

		if (AR4)
		{
			AR4->ThrowMag(Loc, Rot);
		}
	}
}