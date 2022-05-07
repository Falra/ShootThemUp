// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/VDBaseWeapon.h"
#include "VDLauncherWeapon.generated.h"

class AVDProjectile;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API AVDLauncherWeapon : public AVDBaseWeapon
{
    GENERATED_BODY()
public:
    virtual void StartFire() override;
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AVDProjectile> ProjectileClass;
    
    virtual void MakeShot() override;
};
