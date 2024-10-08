// Copyright Epic Games, Inc. All Rights Reserved.


#include "CGameMode.h"
#include "Characters/CPlayer.h"

ACGameMode::ACGameMode()
{
	// 클래스 레퍼런스로 가져오기 위해서는 이름 뒤에 _C가 붙어야 한다.
	ConstructorHelpers::FClassFinder<APawn> PlayerClass(TEXT("Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'"));
	
	if (PlayerClass.Succeeded())
	{
		DefaultPawnClass = PlayerClass.Class;
	}
}