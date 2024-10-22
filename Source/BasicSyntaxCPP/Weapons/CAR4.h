#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAR4.generated.h"

class UAnimMontage;
class ACharacter;

UCLASS()
class BASICSYNTAXCPP_API ACAR4 : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAR4();

public:
	// 이 클래스에 객체를 안 만들어도 호출 가능.
	static ACAR4* Spawn(ACharacter* InOwner);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE bool IsEquipped() { return bEquipped; }
	FORCEINLINE bool IsPlayingMontage() { return bPlayingMontage; }
	FORCEINLINE bool IsAiming() { return bAiming; }

	void EnableAim();
	void DisableAim();

	void Equip();
	void Begin_Equip();
	void End_Equip();

	void UnEquip();
	void Begin_UnEquip();
	void End_UnEquip();

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName HolsterSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Socket")
	FName HandSocket;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* UnEquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	float MontagePlayRate;

private:
	ACharacter* OwnerCharacter;

	bool bEquipped;
	bool bPlayingMontage;
	bool bAiming;
};
