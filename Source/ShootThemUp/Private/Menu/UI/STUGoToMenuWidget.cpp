// Shoot Them Up. All Rights Reserved.


#include "Menu/UI/STUGoToMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GamePlayStatics.h"
#include "STUGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGoToMenuWidget, All, All);

void USTUGoToMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GoToMenuButton)
    {
        GoToMenuButton->OnClicked.AddDynamic(this, &USTUGoToMenuWidget::OnGoToMenu);
    }
}

void USTUGoToMenuWidget::OnGoToMenu()
{
    if (!GetWorld()) return;
    const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
    if (!STUGameInstance) return;

    if (STUGameInstance->GetMenuLevelName().IsNone())
    {
        UE_LOG(LogSTUGoToMenuWidget, Error, TEXT("MenuLevelName is none"));
        return;
    }

    UGameplayStatics::OpenLevel(this, STUGameInstance->GetMenuLevelName());
}
