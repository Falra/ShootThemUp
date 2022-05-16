// Shoot Them Up Game. All Rights Reserved.


#include "VDGameModeBase.h"

#include "AIController.h"
#include "VDRespawnComponent.h"
#include "VDUtils.h"
#include "Player/VDBaseCharacter.h"
#include "Player/VDPlayerController.h"
#include "UI/VDGameHUD.h"
#include "Player/VDPlayerState.h"
#include "EngineUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogVDGameModeBase, All, All);

constexpr static int32 MinRoundTimeForRespawn = 10;

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

    SetMatchState(EVDMatchState::InProgress);
}

UClass* AVDGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if(InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AVDGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
    const auto KillerPlayerState = KillerController ? KillerController->GetPlayerState<AVDPlayerState>() : nullptr;
    const auto VictimPlayerState = VictimController ? VictimController->GetPlayerState<AVDPlayerState>() : nullptr;

    if(KillerPlayerState)
    {
        KillerPlayerState->AddKill();
    }

    if(VictimPlayerState)
    {
        VictimPlayerState->AddDeath();
    }

    StartRespawn(VictimController);
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
            GameOver();
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
        PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
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

void AVDGameModeBase::LogPlayerInfo() const
{
    if(!GetWorld()) return;

    for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if(!Controller) continue;

        const auto PlayerState = Controller->GetPlayerState<AVDPlayerState>();
        if(!PlayerState) continue;

        PlayerState->LogInfo();
    }
}

void AVDGameModeBase::StartRespawn(AController* Controller) const
{
    const auto RespawnAvailable = RoundCountDown > MinRoundTimeForRespawn + GameData.RespawnTime;
    if(!RespawnAvailable) return;
    
    const auto RespawnComponent = VDUtils::GetVDPlayerComponent<UVDRespawnComponent>(Controller);
    if(!RespawnComponent) return;

    RespawnComponent->Respawn(GameData.RespawnTime);
}

void AVDGameModeBase::GameOver()
{
    UE_LOG(LogVDGameModeBase, Display, TEXT("======= GAME OVER ======="));
    LogPlayerInfo();

    for(const auto Pawn: TActorRange<APawn>(GetWorld()))
    {
        if(Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }

    SetMatchState(EVDMatchState::GameOver);
}

void AVDGameModeBase::RespawnRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
}

bool AVDGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);

    if(PauseSet)
    {
        SetMatchState(EVDMatchState::Pause);
    }

    return PauseSet;
}

bool AVDGameModeBase::ClearPause()
{
    const auto PauseCleared = Super::ClearPause();

    if(PauseCleared)
    {
        SetMatchState(EVDMatchState::InProgress);
    }
    
    return PauseCleared;
}

void AVDGameModeBase::SetMatchState(EVDMatchState State)
{
    if(MatchState == State) return;
    
    MatchState = State;
    OnMatchStateChanged.Broadcast(MatchState);
}
