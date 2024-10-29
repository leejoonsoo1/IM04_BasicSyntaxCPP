#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CMagazine.generated.h"

class UStaticMeshComponent;
class OwnerCharacter;

UCLASS()
class BASICSYNTAXCPP_API ACMagazine : public AActor
{
	GENERATED_BODY()
	
public:	
	ACMagazine();

protected:
	virtual void BeginPlay() override;

public:
	FORCEINLINE UStaticMeshComponent* GetMesh() { return MeshComp; }

public:


protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;
};
