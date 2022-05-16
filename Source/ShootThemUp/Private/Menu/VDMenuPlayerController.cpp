// Shoot Them Up Game. All Rights Reserved.


#include "Menu/VDMenuPlayerController.h"

void AVDMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}
