// Shoot Them Up Game. All Rights Reserved.


#include "Player/VDPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogVDPlayerState, All, All);

void AVDPlayerState::LogInfo() const
{
    UE_LOG(LogVDPlayerState, Display, TEXT("Team ID: %i, Kiils: %i, Deaths: %i"), TeamID, KillsNum, DeathsNum);
}
