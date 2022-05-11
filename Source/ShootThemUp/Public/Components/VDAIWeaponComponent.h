// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/VDWeaponComponent.h"
#include "VDAIWeaponComponent.generated.h"

UCLASS()
class SHOOTTHEMUP_API UVDAIWeaponComponent : public UVDWeaponComponent
{
    GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void NextWeapon() override;
};
