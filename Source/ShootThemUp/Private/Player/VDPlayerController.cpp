// Shoot Them Up Game. All Rights Reserved.


#include "Player/VDPlayerController.h"
#include "Components/VDRespawnComponent.h"

AVDPlayerController::AVDPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<UVDRespawnComponent>("RespawnComponent");
}
