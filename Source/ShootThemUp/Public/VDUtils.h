#pragma once
#include "Player/VDPlayerState.h"

class VDUtils
{
public:
    template<typename T>
    static T* GetVDPlayerComponent(AActor* PlayerPawn)
    {
        if(!PlayerPawn) return nullptr;

        const auto Comp = PlayerPawn->FindComponentByClass<T>();
        return Comp;
    }

    bool static AreEnemies(AController* Controller1, AController* Controller2)
    {
        if(!Controller1 || !Controller2 || Controller1 == Controller2) return false;

        const auto PlayerState1 = Controller1->GetPlayerState<AVDPlayerState>();
        const auto PlayerState2 = Controller2->GetPlayerState<AVDPlayerState>();

        return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
    }
};