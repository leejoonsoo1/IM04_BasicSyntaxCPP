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

private: // dynamic delegate�� ������ void Ÿ��.
	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void EndOverlap(AActor* OverlappedActor, AActor* OtherActor);

public: // ���ټ��� ����ؼ� ���� �ۺ����� �Ѵ�.
	FBoxOverlap OnBoxBeginOverlap;
	FBoxOverlap OnBoxEndOverlap;

	FRetValOverlap OnRetValOverlap;
};
