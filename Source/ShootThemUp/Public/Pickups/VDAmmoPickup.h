// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/VDBasePickup.h"
#include "VDAmmoPickup.generated.h"

class AVDBaseWeapon;
UCLASS()
class SHOOTTHEMUP_API AVDAmmoPickup : public AVDBasePickup
{
    GENERATED_BODY()
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
    int32 ClipsAmount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    TSubclassOf<AVDBaseWeapon> WeaponType;
    
private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
