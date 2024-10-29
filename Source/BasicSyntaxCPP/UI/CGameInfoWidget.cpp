#include "CGameInfoWidget.h"
#include "BasicSyntaxCpp.h"
#include "Components/TextBlock.h"
#include "Weapons\CAR4.h"

void UCGameInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACAR4::StaticClass(), FoundACAR4);

    if (FoundACAR4.Num() > 0)
    {
        AR4 = Cast<ACAR4>(FoundACAR4[0]);
    }
}

void UCGameInfoWidget::EnableAutoFire_Implementation()
{
	AutoFireText->SetColorAndOpacity(FSlateColor(FLinearColor::White));
}

void UCGameInfoWidget::DisableAutoFire_Implementation()
{
	AutoFireText->SetColorAndOpacity(FSlateColor(FLinearColor(0.2f, 0.2f, 0.2f, 1.f)));
}

void UCGameInfoWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	int Ammo = AR4->GetCurrentAmmo();
	int MagzineSize = AR4->GetMagazineSize();

	FString temp = FString::FromInt(Ammo) + TEXT(" / ") + FString::FromInt(MagzineSize);
	
	CurrentAmmoText->SetText(FText::FromString(temp));
}