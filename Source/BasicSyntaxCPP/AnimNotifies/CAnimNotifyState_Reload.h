#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CAnimNotifyState_Reload.generated.h"

UCLASS()
class BASICSYNTAXCPP_API UCAnimNotifyState_Reload : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
