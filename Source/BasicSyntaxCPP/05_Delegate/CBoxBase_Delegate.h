// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_Delegate.generated.h"

DECLARE_DELEGATE(FBoxOverlap);// == void __FUNCTION__()
DECLARE_DELEGATE_RetVal_OneParam(FString, FRetValOverlap, FLinearColor); // FSTring FUNCTION(FLinearCOlor InParams

UCLASS()
class BASICSYNTAXCPP_API ACBoxBase_Delegate : public ACBoxBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private: // dynamic delegate는 무조건 void 타입.
	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void EndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public: // 접근성을 고려해서 보통 퍼블릭으로 한다.
	FBoxOverlap OnBoxBeginOverlap;
	FBoxOverlap OnBoxEndOverlap;

	FRetValOverlap OnRetValOverlap;
};
