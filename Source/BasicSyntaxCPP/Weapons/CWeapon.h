#pragma once

#include "CoreMinimal.h"

class BASICSYNTAXCPP_API CWeapon
{
public:
	CWeapon();
	~CWeapon();

protected:
	int32 iMagazine;

public:
	virtual void Reload() = 0;
	virtual void Begin_Reload() = 0;
	virtual void End_Reload() = 0;
};
