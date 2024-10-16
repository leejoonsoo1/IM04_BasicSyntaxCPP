#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLineTrace.generated.h"

class UTextRenderComponent;
class ACVertex;

// Blueprint에서 보여야할 타입이 있어야 하기 때문에 Name을 받는다.
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
	// 이 매크로가 있어야 Blueprint에서도 접근이 가능하다.
	UPROPERTY(BlueprintAssignable)
	FLineTraceHit OnLineTraceHit;
};
