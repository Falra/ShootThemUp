// Shoot Them Up Game. All Rights Reserved.


#include "Menu/VDMenuPlayerController.h"
#include "VDGameInstance.h"

void AVDMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;

    GetWorld()->GetGameInstance<UVDGameInstance>()->TestString = "Menu level says Hello!";
}
