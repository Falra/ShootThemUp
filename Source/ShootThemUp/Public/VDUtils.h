#pragma once

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
};