#include "CStaticMeshActor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

ACStaticMeshActor::ACStaticMeshActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;
}

void ACStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();

	UObject* Asset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/StaticMeshes/MI_StaticMesh"));
	UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(Asset);

	if (MaterialAsset)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(MaterialAsset, nullptr);
		MeshComp->SetMaterial(0, DynamicMaterial);
		
		// 이 함수를 사용하기 위해서는 호출되는 함수는 파라미터를 가지면 안 된다.
		// 리턴 타입도 있으면 안됨.
		UKismetSystemLibrary::K2_SetTimer(this, "ChangeColor", 1.f, true);
	}
}

void ACStaticMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACStaticMeshActor::ChangeColor()
{
	FLinearColor RandomColor;

	RandomColor.R = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
	RandomColor.G = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
	RandomColor.B = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
	RandomColor.A = 1.f;

	// Visual Studio Assist
	DynamicMaterial->SetVectorParameterValue("BaseColor", RandomColor);

	DynamicMaterial->SetScalarParameterValue("Metallic", RandomColor.R);
	DynamicMaterial->SetScalarParameterValue("Roughness", RandomColor.G);

}

