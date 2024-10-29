#include "CAnimNotifyState_Throw_Magazine.h"
#include "Weapons/CWeaponInterface.h"
#include "Weapons/CAR4.h"

void UCAnimNotifyState_Throw_Magazine::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(MeshComp->GetOwner());

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
			AR4->ThrowMag();
		}
	}
}