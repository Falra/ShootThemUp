// Shoot Them Up Game. All Rights Reserved.


#include "VDGameModeBase.h"

#include "AIController.h"
#include "Player/VDBaseCharacter.h"
#include "Player/VDPlayerController.h"
#include "UI/VDGameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogVDGameModeBase, All, All);

AVDGameModeBase::AVDGameModeBase()
{
    DefaultPawnClass = AVDBaseCharacter::StaticClass();
    PlayerControllerClass = AVDPlayerController::StaticClass();
    HUDClass = AVDGameHUD::StaticClass();
}

void AVDGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();

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
            StartRound();
        }
        else
        {
            UE_LOG(LogVDGameModeBase, Display, TEXT("======= GAME OVER ======="));
        }
    }
}
