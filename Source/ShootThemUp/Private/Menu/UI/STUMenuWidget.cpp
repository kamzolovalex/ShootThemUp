// Shoot Them Up. All Rights Reserved.


#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GamePlayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Menu/UI/STULevelItemWidget.h"
#include "Sound/SoundCue.h"
#include "STUGameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUMenuWidget, All, All);

void USTUMenuWidget::NativeOnInitialized() 
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnGameStarted);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnGameQuit);
    }

    InitLevelItems();
}

void USTUMenuWidget::InitLevelItems()
{
    const auto STUGameInstance = GetSTUGameInstance();
    if (!STUGameInstance) return;

    checkf(STUGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

    if (!LevelItemBox) return;
    LevelItemBox->ClearChildren();

    for (auto LevelData: STUGameInstance->GetLevelsData())
    {
        

        const auto LevelItemWidget = CreateWidget<USTULevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!LevelItemWidget) continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &USTUMenuWidget::OnLevelSelected);

        LevelItemBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }

    if (STUGameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(STUGameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(STUGameInstance->GetStartupLevel());
    }
}

void USTUMenuWidget::OnLevelSelected(const FLevelData& Data) 
{
    const auto STUGameInstance = GetSTUGameInstance();
    if (!STUGameInstance) return;

    STUGameInstance->SetStartLevel(Data);

    for (auto LevelItemWidget: LevelItemWidgets)
    {
        if (LevelItemWidget)
        {
            const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

void USTUMenuWidget::OnGameStarted() 
{
    PlayAnimation(PreLoadAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
}

void USTUMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) 
{
    if (Animation != PreLoadAnimation) return;
    const auto STUGameInstance = GetSTUGameInstance();
    if (!STUGameInstance) return;

    UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupLevel().LevelName);
}

void USTUMenuWidget::OnGameQuit() 
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

USTUGameInstance* USTUMenuWidget::GetSTUGameInstance() const
{
    if (!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<USTUGameInstance>();
}