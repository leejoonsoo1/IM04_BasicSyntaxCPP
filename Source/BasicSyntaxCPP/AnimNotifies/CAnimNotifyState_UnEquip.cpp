#include "CAnimNotifyState_UnEquip.h"
#include "Weapons/CWeaponInterface.h"
#include "Weapons/CAR4.h"

FString UCAnimNotifyState_UnEquip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotifyState_UnEquip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// Attach to HankSocket
	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(MeshComp->GetOwner());

	if (OwnerInterface)
	{
		ACAR4* AR4 = OwnerInterface->GetWeapon();

		if (AR4)
		{
			AR4->Begin_UnEquip();
		}
	}
}

void UCAnimNotifyState_UnEquip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	ICWeaponInterface* OwnerInterface = Cast<ICWeaponInterface>(MeshComp->GetOwner());

	if (OwnerInterface)
	{
		ACAR4* AR4 = OwnerInterface->GetWeapon();

		if (AR4)
		{
			AR4->End_UnEquip();
		}
	}
}
