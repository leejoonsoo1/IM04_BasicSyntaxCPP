#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapon.h"
#include "CAR4.generated.h"

class UAnimMontage;
class ACharacter;
class ACBullet;
class USoundCue;
class UStaticMeshComponent;
class UParticleSystem;
class ACMagazine;
class UCGameInfoWidget;

UCLASS()
class BASICSYNTAXCPP_API ACAR4 : public AActor, public CWeapon
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
	FORCEINLINE bool IsFiring() { return bFiring; }
	FORCEINLINE bool IsbAutoFiring() { return bAutoFiring; }
	FORCEINLINE bool IsReLoading() { return bReload; }
	//FORCEINLINE ACAR4* GetAR4() { return this; }
	FORCEINLINE int GetMagazineSize() { return MagazineSize; }
	FORCEINLINE USkeletalMeshComponent* GetMesh() { return MeshComp; }

	UFUNCTION(BlueprintCallable)
	int GetCurrentAmmo();

	void ToggleAutoFiring();

	FORCEINLINE float GetShootRange() { return ShootRange; }

	void EnableAim();
	void DisableAim();

	void Equip();
	void Begin_Equip();
	void End_Equip();

	void UnEquip();
	void Begin_UnEquip();
	void End_UnEquip();

	void SpawnMag(FName Socket);
	void ThrowMag(FVector Location, FRotator Rotation);

	void DestroyMag();

public:
	void OnFire();
	void OffFire();

	void Reload() override;
	void Begin_Reload() override;
	void End_Reload() override;

private:
	UFUNCTION()
	void Firing_Internal();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	int CurrentAmmo;

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
	UAnimMontage* ReLoadMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	float MontagePlayRate;

	UPROPERTY(EditDefaultsOnly, Category = "Range")
	float ShootRange;

	UPROPERTY(EditDefaultsOnly, Category = "CameraShake")
	TSubclassOf<UCameraShake> ShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	TSubclassOf<ACBullet> BulletClass;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	TSubclassOf<ACMagazine> MagazineClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	UParticleSystem* EjectEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	UMaterial* DecalMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	float PitchSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Magazine")
	UStaticMeshComponent* MagComp;

private:
	ACharacter* OwnerCharacter;
	CWeapon* Weapon;
	ACMagazine* Mag;
	UCGameInfoWidget* GameInfoWidget;

	bool bEquipped;
	bool bPlayingMontage;
	bool bAiming;
	bool bFiring;
	bool bReload;
	bool bAutoFiring;
	
	FTimerHandle AutoFireTimer;
	FTimerHandle TimeHandle;

	float CurrentPitch;

	int MagazineSize;
};