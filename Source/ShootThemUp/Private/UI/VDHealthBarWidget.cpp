// Shoot Them Up Game. All Rights Reserved.


#include "UI/VDHealthBarWidget.h"
#include "Components/ProgressBar.h"

void UVDHealthBarWidget::SetHealthPercent(float Percent)
{
    if (!HealthBar) return;

    const auto HealthVisibility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent)) //
                                ? ESlateVisibility::Hidden
                                : ESlateVisibility::Visible;
    HealthBar->SetVisibility(HealthVisibility);

    const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
    HealthBar->SetFillColorAndOpacity(HealthBarColor);

    HealthBar->SetPercent(Percent);
}
