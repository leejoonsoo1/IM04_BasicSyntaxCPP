#include "CBall.h"
#include "Materials\MaterialInstanceConstant.h"
#include "Kismet/GameplayStatics.h"
#include "CBoxBase_Multicast.h"
#include "Utilities/CLog.h"

// Sets default values
ACBall::ACBall()
{
	Pi = 3.14f;

	RootSceneComp = CreateDefaultSubobject<USceneComponent>("RootSceneComp");
	RootComponent = RootSceneComp;

	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StaticMeshes/SM_Sphere"));

	for (int32 i = 0; i < 3; i++)
	{
		FString SubObjectName;
		SubObjectName.Append("MeshComp");
		SubObjectName.Append(FString::FromInt(i + 1));

		MeshComps[i] = CreateDefaultSubobject<UStaticMeshComponent>(FName(SubObjectName));
		MeshComps[i]->SetupAttachment(RootComponent);
		MeshComps[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		
		if (MeshAsset.Succeeded()) 
		{
			MeshComps[i]->SetStaticMesh(MeshAsset.Object);
		}
	}
}

// Called when the game starts or when spawned
void ACBall::BeginPlay()
{
	Super::BeginPlay();

	// Get Material Asset
	UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/StaticMeshes/MI_StaticMesh")));

	for (int32 i = 0; i < 3; i++)
	{
		// Set World Location of MeshComponent
		FTransform TM = MeshComps[i]->GetComponentToWorld();
		OriginLocation[i] = TM.GetLocation();

		// Set Dynamic Matetrial
		if (MaterialAsset)
		{
			DynamicMaterials[i] = UMaterialInstanceDynamic::Create(MaterialAsset, nullptr);
			MeshComps[i]->SetMaterial(0, DynamicMaterials[i]);
		}
	}

	// Bind Multicast Event
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACBoxBase_Multicast::StaticClass(), Actors);

	ACBoxBase_Multicast* Box = Cast<ACBoxBase_Multicast>(Actors[0]);

	if (Box)
	{
		Box->OnBoxMulticast.AddUObject(this, &ACBall::Drop);

		// 람다 함수는 함수 영역 밖에 변수에 접근할 수 없다.
		Box->OnBoxMulticast.AddLambda([=](int32 InIndex, FLinearColor InColor)
			{
				FString Log = FString::Printf(TEXT("[Pi = %f], RandomIndex is %d"), Pi, InIndex);
				CLog::Log(Log);
			});
	}
}

void ACBall::Drop(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; i++)
	{
		MeshComps[i]->SetSimulatePhysics(false);
		MeshComps[i]->SetWorldLocation(OriginLocation[i]);

		DynamicMaterials[i]->SetVectorParameterValue("BaseColor", FVector(0.25f, 0.25f, 0.25f));
	}

	MeshComps[InIndex]->SetSimulatePhysics(true);
	DynamicMaterials[InIndex]->SetVectorParameterValue("BaseColor",InColor);
}
