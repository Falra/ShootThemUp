// Shoot Them Up Game. All Rights Reserved.


#include "UI/VDGameDataWidget.h"
#include "VDGameModeBase.h"
#include "VDPlayerController.h"
#include "Player/VDPlayerState.h"

int32 UVDGameDataWidget::GetKillsNum() const
{
    const auto PlayerState = GetPlayerState();
    if(!PlayerState) return 0;

    return PlayerState->GetKillsNum();
}

int32 UVDGameDataWidget::GetDeathsNum() const
{
    const auto PlayerState = GetPlayerState();
    if(!PlayerState) return 0;

    return PlayerState->GetDeathsNum() ;
}

int32 UVDGameDataWidget::GetCurrentRoundNum() const
{
    const auto GameMode = GetGameMode();
    if(!GameMode) return 0;

    return GameMode->GetCurrentRoundNum();
}

int32 UVDGameDataWidget::GetTotalRoundsNum() const
{
    const auto GameMode = GetGameMode();
    if(!GameMode) return 0;

    return GameMode->GetGameData().RoundsNum;
}

int32 UVDGameDataWidget::GerRoundSecondsRemaining() const
{
    const auto GameMode = GetGameMode();
    if(!GameMode) return 0;

    return GameMode->GetRoundSecondsRemaining();
}

AVDGameModeBase* UVDGameDataWidget::GetGameMode() const
{
    return GetWorld() ? Cast<AVDGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

AVDPlayerState* UVDGameDataWidget::GetPlayerState() const
{
    return GetOwningPlayer() ? GetOwningPlayer()->GetPlayerState<AVDPlayerState>() : nullptr;
}
