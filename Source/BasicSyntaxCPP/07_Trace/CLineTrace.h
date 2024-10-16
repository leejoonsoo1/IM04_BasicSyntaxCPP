#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLineTrace.generated.h"

class UTextRenderComponent;
class ACVertex;

// Blueprint���� �������� Ÿ���� �־�� �ϱ� ������ Name�� �޴´�.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FLineTraceHit, AActor*, InActor, FLinearColor, InColor);

UCLASS()
class BASICSYNTAXCPP_API ACLineTrace : public AActor
{
	GENERATED_BODY()
	
public:	
	ACLineTrace();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* RootSceneComp; // != RootComponent

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UTextRenderComponent* TextRenderComp;

private:
	UFUNCTION()
	void LineTraceHit(AActor* InActor, FLinearColor InColor);

private:
	ACVertex* Vertices[2];

public:
	// �� ��ũ�ΰ� �־�� Blueprint������ ������ �����ϴ�.
	UPROPERTY(BlueprintAssignable)
	FLineTraceHit OnLineTraceHit;
};
