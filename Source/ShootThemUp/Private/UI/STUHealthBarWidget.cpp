// Shoot Them Up. All Rights Reserved.


#include "UI/STUHealthBarWidget.h"
#include "Components/ProgressBar.h"

void USTUHealthBarWidget::SetHealthPercent(float Percent) 
{
    if (!HealthProgressBar) return;
    
    const auto HealBarVisibility =
        (Percent > PercentVisibilityThereshold || FMath::IsNearlyZero(Percent)) ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
    HealthProgressBar->SetVisibility(HealBarVisibility);

    const auto HealthBarColor = Percent > PercentColorThershold ? GoodColor : BadColor;
    HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

    HealthProgressBar->SetPercent(Percent);
}