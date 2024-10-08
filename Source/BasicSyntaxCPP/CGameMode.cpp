// Copyright Epic Games, Inc. All Rights Reserved.


#include "CGameMode.h"
#include "Characters/CPlayer.h"

ACGameMode::ACGameMode()
{
	// Ŭ���� ���۷����� �������� ���ؼ��� �̸� �ڿ� _C�� �پ�� �Ѵ�.
	ConstructorHelpers::FClassFinder<APawn> PlayerClass(TEXT("Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'"));
	
	if (PlayerClass.Succeeded())
	{
		DefaultPawnClass = PlayerClass.Class;
	}
}