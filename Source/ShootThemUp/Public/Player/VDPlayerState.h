// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "VDPlayerState.generated.h"

UCLASS()
class SHOOTTHEMUP_API AVDPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    int32 GetTeamID() const { return TeamID; }
    void SetTeamID(int32 ID) { TeamID = ID;}

    FLinearColor GetTeamColor() const { return TeamColor; }
    void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }

    void AddKill() { ++KillsNum; }
    int32 GetKillsNum() const { return KillsNum; }

    void AddDeath() { ++DeathsNum; }
    int32 GetDeathsNum() const { return DeathsNum; }

    void LogInfo() const;
    
private:
    int32 TeamID;
    FLinearColor TeamColor;

    int32 KillsNum = 0;
    int32 DeathsNum = 0;
};
