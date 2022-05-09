// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/VDBasePickup.h"
#include "VDHealthPickup.generated.h"

UCLASS()
class SHOOTTHEMUP_API AVDHealthPickup : public AVDBasePickup
{
    GENERATED_BODY()
private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
