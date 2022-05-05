// Shoot Them Up Game. All Rights Reserved.


#include "VDGameModeBase.h"

#include "Player/VDBaseCharacter.h"
#include "Player/VDPlayerController.h"
#include "UI/VDGameHUD.h"

AVDGameModeBase::AVDGameModeBase()
{
    DefaultPawnClass = AVDBaseCharacter::StaticClass();
    PlayerControllerClass = AVDPlayerController::StaticClass();
    HUDClass = AVDGameHUD::StaticClass();
}
