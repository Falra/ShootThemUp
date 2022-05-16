// Shoot Them Up Game. All Rights Reserved.


#include "Menu/VDMenuGameModeBase.h"
#include "Menu/VDMenuPlayerController.h"
#include "Menu/UI/VDMenuHUD.h"

AVDMenuGameModeBase::AVDMenuGameModeBase()
{
    PlayerControllerClass = AVDMenuPlayerController::StaticClass();
    HUDClass = AVDMenuHUD::StaticClass();
}
