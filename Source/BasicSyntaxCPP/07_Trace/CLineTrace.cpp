#include "CLineTrace.h"
#include "BasicSyntaxCpp.h"
#include "Components/TextRenderComponent.h"
#include "CVertex.h"

ACLineTrace::ACLineTrace()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &RootSceneComp, "RootSceneComp");
	CHelpers::CreateSceneComponent(this, &TextRenderComp, "TextRenderComp", RootSceneComp);

	TextRenderComp->SetRelativeLocation(FVector(0, 0, 20));
	TextRenderComp->SetRelativeRotation(FRotator(0, 180, 0));
	TextRenderComp->SetTextRenderColor(FColor::Red);
	TextRenderComp->SetHorizontalAlignment(EHTA_Center);
	TextRenderComp->SetText(GetName());
}

void ACLineTrace::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACVertex::StaticClass(), Actors);
	
	if (Actors.Num() < 1) return;

	Vertices[0] = Cast<ACVertex>(Actors[0]);
	Vertices[1] = Cast<ACVertex>(Actors[1]);

	OnLineTraceHit.AddDynamic(this, &ACLineTrace::LineTraceHit);
}

// 이벤트 기반을 쓰면 Tick 함수가 필요가 없어진다.
void ACLineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// DrawDebug를 사용하지 않음. 아래 함수보다 가벼운 함수.
	//GetWorld()->LineTraceSingleByObjectType();
	
	FVector Start = Vertices[0]->GetActorLocation();
	FVector End = Vertices[1]->GetActorLocation();

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(Vertices[0]);
	IgnoreActors.Add(Vertices[1]);

	FHitResult Hit;
	// LineTrace DrawDebug를 통해서 사용. 위 함수보다 무거운 함수.
	UKismetSystemLibrary::LineTraceSingleByProfile(GetWorld(), Start, End, "Pawn", false, IgnoreActors, EDrawDebugTrace::ForOneFrame, Hit, true);
	
	if (Hit.bBlockingHit == false) return;

	OnLineTraceHit.Broadcast(Hit.GetActor(), FLinearColor::Red);
}

void ACLineTrace::LineTraceHit(AActor* InActor, FLinearColor InColor)
{
	TextRenderComp->SetTextRenderColor(InColor.ToFColor(true));
	TextRenderComp->SetText(InActor->GetName());
}