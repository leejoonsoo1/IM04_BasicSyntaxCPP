#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CGameInfoWidget.generated.h"

class UTextBlock;
class ACAR4;

UCLASS()
class BASICSYNTAXCPP_API UCGameInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION(BlueprintNativeEvent)
	void EnableAutoFire();

	UFUNCTION(BlueprintNativeEvent)
	void DisableAutoFire();

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AutoFireText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentAmmoText;

private:
	TArray<AActor*> FoundACAR4;
	ACAR4* AR4;
};
