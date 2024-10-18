#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapons/CWeaponInterface.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMaterialInstanceDynamic;
class ACAR4;

UCLASS()
class BASICSYNTAXCPP_API ACPlayer : public ACharacter, public ICWeaponInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Inherited via ICWeaponInterface
	FORCEINLINE ACAR4* GetWeapon() override { return AR4; }

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	
	void OnSprint();
	void OffSprint();

	void OnRifle();

public:
	UFUNCTION(BlueprintCallable)
	void SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor);

	UFUNCTION(BlueprintCallable)
	void ResetBodyColor();
	// 오늘 학원가면 할 거.
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;
	
	// Our Main View Target
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComp;	
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* BackPackComp;

	UPROPERTY(EditDefaultsOnly, Category = "Class")
	TSubclassOf<ACAR4> WeaponClass;

private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;

	ACAR4* AR4;
};