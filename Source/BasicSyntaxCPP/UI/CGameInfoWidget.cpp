#include "CGameInfoWidget.h"
#include "BasicSyntaxCpp.h"
#include "Components/TextBlock.h"

void UCGameInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCGameInfoWidget::EnableAutoFire_Implementation()
{
	AutoFireText->SetColorAndOpacity(FSlateColor(FLinearColor::White));
}

void UCGameInfoWidget::DisableAutoFire_Implementation()
{
	AutoFireText->SetColorAndOpacity(FSlateColor(FLinearColor(0.2f, 0.2f, 0.2f, 1.f)));
}
