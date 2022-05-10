// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/VDBaseWeapon.h"
#include "VDRifleWeapon.generated.h"

class UVDWeaponFXComponent;
class UNiagaraComponent;

UCLASS()
class SHOOTTHEMUP_API AVDRifleWeapon : public AVDBaseWeapon
{
    GENERATED_BODY()

public:
    AVDRifleWeapon();

    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TimeBetweenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float BulletSpread = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float DamageAmount = 10.0f;

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    UVDWeaponFXComponent* WeaponFXComponent;

    virtual void BeginPlay() override;

    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
    FTimerHandle ShotTimerHandle;

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;

    void MakeDamage(const FHitResult& HitResult);
    void InitMuzzleFX();
    void SetMuzzleFXVisibility(bool Visible);
};
