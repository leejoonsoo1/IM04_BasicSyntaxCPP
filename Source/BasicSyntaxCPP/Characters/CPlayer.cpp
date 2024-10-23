// Fill out your copyright notice in the Description page of Project Settings.

#include "CPlayer.h"
#include "BasicSyntaxCpp.h"
#include "GameFramework\SpringArmComponent.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "Camera\CameraComponent.h"
#include "Components\StaticMeshComponent.h"
#include "Weapons\CAR4.h"
#include "Blueprint/UserWidget.h"
#include "UI/CAimWidget.h"

// Sets default values
ACPlayer::ACPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create Camera Component
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");

	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 60));
	SpringArmComp->SocketOffset = FVector(0, 60, 0);
	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	// Set Skeletal Mesh Asset
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Character/Mesh/SK_Mannequin"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

		ConstructorHelpers::FClassFinder<UAnimInstance> AnimClass(TEXT("/Game/Player/ABP_CPlayer"));

		if (AnimClass.Succeeded())
		{
			GetMesh()->SetAnimInstanceClass(AnimClass.Class);
		}
	}

	// Set BackPack Asset
	BackPackComp = CreateDefaultSubobject<UStaticMeshComponent>("BackPackComp");
	ConstructorHelpers::FObjectFinder<UStaticMesh> BackPackMeshAsset(TEXT("/Game/StaticMeshes/Backpack/Backpack"));

	if (BackPackMeshAsset.Succeeded())
	{
		BackPackComp->SetStaticMesh(BackPackMeshAsset.Object);
	}

	BackPackComp->SetupAttachment(GetMesh(), "Backpack");	

	CHelpers::GetClass(&WeaponClass, "/Game/AR4/BP_CAR4");

	//Character Movement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;

	// Get Aim Widget Class Asset
	CHelpers::GetClass(&AimWidgetClass, "/Game/UI/WB_Aim");


}

// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	// Set Dynamic Material
	BodyMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), nullptr);
	LogoMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(1), nullptr);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	// Spawn AR4
	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	AR4 = GetWorld()->SpawnActor<ACAR4>(WeaponClass, SpawnParam);

	// Create Aim Widget
	AimWidget = CreateWidget<UCAimWidget>(GetController<APlayerController>(), AimWidgetClass);
	AimWidget->AddToViewport();
	AimWidget->SetVisibility(ESlateVisibility::Hidden);
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
// 액션 이벤트나 축이벤트가 눌렸을때 무슨 기능을 할지 작성하는 함수
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACPlayer::OnSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACPlayer::OffSprint);

	PlayerInputComponent->BindAction("Rifle", IE_Pressed, this, &ACPlayer::OnRifle);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ACPlayer::OffAim);

}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator ControlRot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRot).GetForwardVector();

	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator ControlRot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRot).GetRightVector();

	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void ACPlayer::OffSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 400;
}

void ACPlayer::OnRifle()
{
	if (AR4->IsEquipped())
	{
		if (AR4->IsAiming())
		{
			OffAim();
		}

		AR4->UnEquip();
		return;
	}

	AR4->Equip();
}

void ACPlayer::SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor)
{
	// Vector Parameter에 이름이 BodyColor이기 때문에 BodyColor를 매개변수로 준다.
	BodyMaterial->SetVectorParameterValue("BodyColor", InBodyColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InLogoColor);
}

void ACPlayer::ResetBodyColor()
{
	SetBodyColor
	(
		FLinearColor(0.45098f, 0.403922f, 0.360784f),
		FLinearColor(0.45098f, 0.403922f, 0.360784f)
	);
}

void ACPlayer::GetAimInRay(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection)
{
	OutAimDirection = CameraComp->GetForwardVector();

	OutAimStart = CameraComp->GetComponentToWorld().GetLocation();
	OutAimEnd = OutAimStart + OutAimDirection * AR4->GetShootRange();

	//FVector MuzzleSocketLoction = AR4->GetMesh()->GetSocketLocation("MuzzleFlash");

}

void ACPlayer::OnAim()
{
	if (!AR4->IsEquipped()) return;
	if (AR4->IsPlayingMontage()) return;

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	SpringArmComp->TargetArmLength = 100.f;
	SpringArmComp->SocketOffset = FVector(0, 30, 10);

	AR4->EnableAim();

	ZoomIn();

	// 보여지긴 하지만, 위젯과 마우스 충돌을 감지하지 않는다.
	AimWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void ACPlayer::OffAim() 
{
	if (!AR4->IsEquipped()) return;
	if (AR4->IsPlayingMontage()) return;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->SocketOffset = FVector(0, 60, 0);

	AR4->DisableAim();

	ZoomOut();

	AimWidget->SetVisibility(ESlateVisibility::Hidden);
}
