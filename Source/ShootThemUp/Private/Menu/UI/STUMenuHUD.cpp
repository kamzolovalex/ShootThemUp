// Shoot Them Up. All Rights Reserved.


#include "Menu/UI/STUMenuHUD.h"
#include "UI/STUBaseWidget.h"


void ASTUMenuHUD::BeginPlay() 
{
    Super::BeginPlay();

    const auto MunuWidget = CreateWidget<USTUBaseWidget>(GetWorld(), MenuWidjetClass);

    if (MunuWidget)
    {
        MunuWidget->AddToViewport();
        MunuWidget->Show();
    }
}