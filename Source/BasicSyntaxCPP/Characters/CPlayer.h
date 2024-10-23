#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapons/CWeaponInterface.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMaterialInstanceDynamic;
class ACAR4;
class UCAimWidget;
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
	void GetAimInRay(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection) override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void ZoomIn();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ZoomOut();

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	
	void OnSprint();
	void OffSprint();

	void OnAim();
	void OffAim();

	void OnRifle();

public:
	UFUNCTION(BlueprintCallable)
	void SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor);

	UFUNCTION(BlueprintCallable)
	void ResetBodyColor();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;
	
	// Our Main View Target
	UPROPERTY(BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;	
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* BackPackComp;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TSubclassOf<ACAR4> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UCAimWidget> AimWidgetClass;

private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;

	ACAR4* AR4;
	UCAimWidget* AimWidget;
};