
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProperty.generated.h"

UCLASS()
class BASICSYNTAXCPP_API ACProperty : public AActor
{
	GENERATED_BODY()
	
public:	
	ACProperty();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly, Category = "Numeric", BluePrintReadOnly)
	int32 NumA = 10;
	
	UPROPERTY(EditDefaultsOnly, Category = "Numeric", BluePrintReadOnly)
	int32 NumB;

	UPROPERTY(EditAnyWhere, Category = "Numeric", BluePrintReadWrite)
	int32 NumC = 30;

private:
	UPROPERTY(VisibleInstanceOnly, Category = "Real")
	float RealA = 1.11f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Real")
	float RealB = 2.22f;

	UPROPERTY(VisibleAnyWhere, Category = "Real")
	float RealC = 3.33f;

	UPROPERTY(EditAnyWhere, Category = "MyActor")
	AActor* OtherActor;
};
