// Shoot Them Up Game. All Rights Reserved.


#include "VDGameModeBase.h"

#include "AIController.h"
#include "Player/VDBaseCharacter.h"
#include "Player/VDPlayerController.h"
#include "UI/VDGameHUD.h"
#include "Player/VDPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogVDGameModeBase, All, All);

AVDGameModeBase::AVDGameModeBase()
{
    DefaultPawnClass = AVDBaseCharacter::StaticClass();
    PlayerControllerClass = AVDPlayerController::StaticClass();
    HUDClass = AVDGameHUD::StaticClass();
    PlayerStateClass = AVDPlayerState::StaticClass();
}

void AVDGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();
    CreateTeamsInfo();
    
    CurrentRound = 1;
    StartRound();
}

UClass* AVDGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if(InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AVDGameModeBase::SpawnBots()
{
    if(!GetWorld() || GameData.PlayersNum == 1) return;

    FActorSpawnParameters SpawnInfo;
    SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    for(int32 i = 0; i < GameData.PlayersNum - 1; ++i)
    {
        const auto SpawnAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(SpawnAIController);
    }
}

void AVDGameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundsTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AVDGameModeBase::GameTimerUpdate, 1.0f, true);
}

void AVDGameModeBase::GameTimerUpdate()
{
    UE_LOG(LogVDGameModeBase, Display, TEXT("Time: %i / Round: %i / %i"), RoundCountDown, CurrentRound, GameData.RoundsNum);

    // const auto TimerRate = GetWorldTimerManager().GetTimerRate(GameRoundTimerHandle);
    // RoundCountDown -= TimerRate;
    
    if(--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

        if(++CurrentRound <= GameData.RoundsNum)
        {
            ResetPlayers();
            StartRound();
        }
        else
        {
            UE_LOG(LogVDGameModeBase, Display, TEXT("======= GAME OVER ======="));
        }
    }
}

void AVDGameModeBase::ResetPlayers()
{
    if(!GetWorld()) return;

    for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void AVDGameModeBase::ResetOnePlayer(AController* Controller)
{
    if(Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    
    RestartPlayer(Controller);
    SerPlayerColor(Controller);
}

void AVDGameModeBase::CreateTeamsInfo()
{
    if(!GetWorld()) return;

    int32 TeamID = 1;
    for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if(!Controller) continue;

        const auto PlayerState = Controller->GetPlayerState<AVDPlayerState>();
        if(!PlayerState) continue;

        PlayerState->SetTeamID(TeamID);
        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
        SerPlayerColor(Controller);
        
        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor AVDGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
    if(TeamID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamID - 1];
    }
    UE_LOG(LogVDGameModeBase, Warning, TEXT("No color for team ID: %i, set to default: %s"), TeamID, *GameData.DefaultTeamColor.ToString());
    return GameData.DefaultTeamColor;;
}

void AVDGameModeBase::SerPlayerColor(AController* Controller)
{
    if(!Controller) return;

    const auto Character = Cast<AVDBaseCharacter>(Controller->GetPawn());
    if(!Character) return;

    const auto PlayerState = Controller->GetPlayerState<AVDPlayerState>();
    if(!PlayerState) return;

    Character->SetPlayerColor(PlayerState->GetTeamColor());
}
