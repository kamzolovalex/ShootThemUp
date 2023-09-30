// Shoot Them Up. All Rights Reserved.


#include "Menu/STUMenuPlayerController.h"
#include "Camera/CameraActor.h"

void ASTUMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}