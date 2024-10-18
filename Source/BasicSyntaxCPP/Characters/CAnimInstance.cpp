// Fill out your copyright notice in the Description page of Project Settings.

#include "CAnimInstance.h"
#include "Weapons\CWeaponInterface.h"
#include "Weapons/CAR4.h"

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!TryGetPawnOwner())
	{
		return;
	}

	Speed = TryGetPawnOwner()->GetVelocity().Size2D();

	// 포즈 바꾸는데 사용하기 위함.
	ICWeaponInterface* Owner = Cast<ICWeaponInterface>(TryGetPawnOwner());
	if (Owner && Owner->GetWeapon())
	{
		bEquipped = Owner->GetWeapon()->IsEquipped();
	}
}