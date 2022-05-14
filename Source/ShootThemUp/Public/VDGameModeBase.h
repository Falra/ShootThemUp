// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VDCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "VDGameModeBase.generated.h"

class AAIController;

UCLASS()
class SHOOTTHEMUP_API AVDGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    AVDGameModeBase();

    FOnMatchStateChangedSignature OnMatchStateChanged;
    
    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

    void Killed(AController* KillerController, AController* VictimController);

    FGameData GetGameData() const { return GameData; }
    int32 GetCurrentRoundNum() const { return CurrentRound; }
    int32 GetRoundSecondsRemaining() const { return RoundCountDown; }

    void RespawnRequest(AController* Controller);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;
    
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

private:
    EVDMatchState MatchState = EVDMatchState::WaitingToStart;
    int32 CurrentRound = 1;
    int32 RoundCountDown = 0;
    FTimerHandle GameRoundTimerHandle;
    
    void SpawnBots();
    void StartRound();
    void GameTimerUpdate();

    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void CreateTeamsInfo();
    FLinearColor DetermineColorByTeamID(int32 TeamID) const;
    void SerPlayerColor(AController* Controller);

    void StartRespawn(AController* Controller) const;

    void GameOver();
    
    void LogPlayerInfo() const;
    void SetMatchState(EVDMatchState State);
};
