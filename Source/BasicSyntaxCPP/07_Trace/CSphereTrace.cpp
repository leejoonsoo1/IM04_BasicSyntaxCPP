#include "CSphereTrace.h"
#include "BasicSyntaxCpp.h"
#include "Components/TextRenderComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework\Character.h"

ACSphereTrace::ACSphereTrace()
{
	CHelpers::CreateSceneComponent(this, &ParticleComp, "ParticleComp");
	
	UParticleSystem* ParticleAsset;
	CHelpers::GetAsset(&ParticleAsset, "/Game/Explosions/Particles/P_ImpactExplosion4");
	ParticleComp->SetTemplate(ParticleAsset);
	ParticleComp->SetAutoActivate(false);

	
	CHelpers::CreateSceneComponent(this, &TextRenderComp, "TextRenderComp", ParticleComp);
	TextRenderComp->SetRelativeLocation(FVector(0, 0, 20));
	TextRenderComp->SetRelativeRotation(FRotator(0, 180, 0));
	TextRenderComp->SetTextRenderColor(FColor::Red);
	TextRenderComp->SetHorizontalAlignment(EHTA_Center);
	TextRenderComp->SetText(GetName());

	Strength = 15e+6;
}

void ACSphereTrace::BeginPlay()
{
	Super::BeginPlay();
}

void ACSphereTrace::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->IsA<ACharacter>() == false) 
		return;
	
	FVector Start = GetActorLocation();
	FVector End = Start + FVector(0, 0, 10);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(ObjectTypeQuery4);
	// ECollisionChannel	-> 내 충돌체 타입
	// EObjectTypeQuery		-> 다른 충돌체 질의

	TArray<AActor*> Ignores;
	TArray<FHitResult> Hits;
		
	if (UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, 1000, ObjectTypes, false, Ignores, EDrawDebugTrace::ForDuration, Hits, true))
	{
		ParticleComp->ResetParticles();
		ParticleComp->SetActive(true);

		// 레퍼런스로 받을 수 있다.
		for (const auto& Hit : Hits)
		{
			UPrimitiveComponent* HitComp = Hit.GetComponent();

			HitComp->AddRadialImpulse(GetActorLocation(), 1000, Strength / HitComp->GetMass(), ERadialImpulseFalloff::RIF_Linear);
		}
	}
}