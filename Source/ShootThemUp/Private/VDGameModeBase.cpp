// Shoot Them Up Game. All Rights Reserved.


#include "VDGameModeBase.h"

#include "AIController.h"
#include "Player/VDBaseCharacter.h"
#include "Player/VDPlayerController.h"
#include "UI/VDGameHUD.h"

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
