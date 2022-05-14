// Shoot Them Up Game. All Rights Reserved.


#include "Components/VDRespawnComponent.h"
#include "VDGameModeBase.h"

UVDRespawnComponent::UVDRespawnComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UVDRespawnComponent::Respawn(int32 RespawnTime)
{
    if(!GetWorld()) return;

    RespawnCountDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UVDRespawnComponent::RespawnTimerUpdate, 1.0f,  true);
}

void UVDRespawnComponent::RespawnTimerUpdate()
{
    if(--RespawnCountDown == 0)
    {
        if(!GetWorld()) return;
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

        const auto GameMode = Cast<AVDGameModeBase>(GetWorld()->GetAuthGameMode());
        if(!GameMode) return;

        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}
