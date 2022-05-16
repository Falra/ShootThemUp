// Shoot Them Up Game. All Rights Reserved.


#include "UI/VDGameOverWidget.h"
#include "VDGameModeBase.h"
#include "VDUtils.h"
#include "Player/VDPlayerState.h"
#include "UI/VDPlayerStatRowWidget.h"
#include "Components/VerticalBox.h"

bool UVDGameOverWidget::Initialize()
{
    if(GetWorld())
    {
        const auto GameMode = Cast<AVDGameModeBase>(GetWorld()->GetAuthGameMode());
        if(GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &UVDGameOverWidget::OnMatchStateChanged);
        }
    }
    
    return Super::Initialize();
}

void UVDGameOverWidget::OnMatchStateChanged(EVDMatchState State)
{
    if(State == EVDMatchState::GameOver)
    {
        UpdatePlayerStat();
    }
}

void UVDGameOverWidget::UpdatePlayerStat()
{
    if(!GetWorld() || !PlayerStatBox) return;

    PlayerStatBox->ClearChildren();
    
    for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if(!Controller) continue;

        const auto PlayerState = Controller->GetPlayerState<AVDPlayerState>();
        if(!PlayerState) continue;

        const auto PlayerStatRowWidget = CreateWidget<UVDPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        if(!PlayerStatRowWidget) continue;

        PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatRowWidget->SetKills(VDUtils::TextFromInt(PlayerState->GetKillsNum()));
        PlayerStatRowWidget->SetDeaths(VDUtils::TextFromInt(PlayerState->GetDeathsNum()));
        PlayerStatRowWidget->SetTeam(VDUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

        PlayerStatBox->AddChild(PlayerStatRowWidget);
    }
}
