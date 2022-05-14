// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VDCoreTypes.h"
#include "GameFramework/Actor.h"
#include "VDBaseWeapon.generated.h"

class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class SHOOTTHEMUP_API AVDBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    AVDBaseWeapon();

    FOnClipEmptySignature OnClipEmpty;
    
    virtual void StartFire();
    virtual void StopFire();
    bool IsFiring() const;

    void ChangeClip();
    bool CanReload() const;
    bool IsAmmoEmpty() const;
    bool IsAmmoFull() const;
    
    FWeaponUIData GetUIData() const { return UIData; }
    FAmmoData GetAmmoData() const { return CurrentAmmo; }
    bool TryToAddAmmo(int32 ClipsAmount);

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleFlashSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 1500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{15, 10, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* MuzzleFX;
    
    bool FireInProgress = false;
    
    virtual void BeginPlay() override;

    virtual void MakeShot();
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;

    void DecreaseAmmo();
    bool IsClipEmpty() const;
    
    void LogAmmo();

    UNiagaraComponent* SpawnMuzzleFX();
    
private:
    FTimerHandle ShotTimerHandle;
    FAmmoData CurrentAmmo;
};
