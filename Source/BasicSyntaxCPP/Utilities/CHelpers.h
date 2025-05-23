#pragma once

#include "CoreMinimal.h"

class CHelpers
{
public:
	template<typename T>
	static void GetAsset(T** OutAsset, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> Asset(*InPath);
		ensureMsgf(Asset.Succeeded(), TEXT("Asset not found"));

		*OutAsset = Asset.Object;
	}

	template<typename T>
	static void GetClass(TSubclassOf<T>* OutClass, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> AssetClass(*InPath);

		ensureMsgf(AssetClass.Succeeded(), TEXT("Class not found"));
		*OutClass = AssetClass.Class;
	}

	template<typename T>
	static void CreateSceneComponent(AActor* InObject, T** OutComp, FName InName, USceneComponent* InParent = nullptr)
	{
		(*OutComp) = InObject->CreateDefaultSubobject<T>(InName);
		
		if (InParent)
		{
			(*OutComp)->SetupAttachment(InParent);
		}
		else
		{
			InObject->SetRootComponent(*OutComp);
		}
	}

	template<typename T>
	static void CreateActorComponent(AActor* InObject, T** OutComp, FName InName)
	{
		(*OutComp) = InObject->CreateDefaultSubobject<T>(InName);
	}
};