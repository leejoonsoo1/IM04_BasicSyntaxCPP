#include "CBoxBase_Multicast.h"
#include "Kismet/KismetMathLibrary.h"

void ACBoxBase_Multicast::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACBoxBase_Multicast::BeginOverlap);
}

void ACBoxBase_Multicast::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, 2);
	FLinearColor RandomColor = FLinearColor::MakeRandomColor();
	RandomColor.A = 1.f;

	// 브로드 캐스트 안에 For문을 돌리기 때문에 굳이 is Bound를 안 해도 된다.
	OnBoxMulticast.Broadcast(RandomIndex, RandomColor);
}
