// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VDAmmoPickup.h"
#include "VDBaseWeapon.h"
#include "VDCoreTypes.h"
#include "VDNeedAmmoDecorator.h"
#include "Components/ActorComponent.h"
#include "VDWeaponComponent.generated.h"

class AVDBaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API UVDWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UVDWeaponComponent();

    virtual void StartFire();
    void StopFire();
    bool IsFiring() const;
    virtual void NextWeapon();
    void Reload();

    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;
    
    bool TryToAddAmmo(const TSubclassOf<AVDBaseWeapon>& WeaponType, int32 ClipsAmount);
    bool NeedAmmo(const TSubclassOf<AVDBaseWeapon>& WeaponType);

    void Zoom(bool Enabled);
    
protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponPoint";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY()
    AVDBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<AVDBaseWeapon*> Weapons;
    
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage;

    int32 CurrentWeaponIndex = 0;
    
    bool CanFire() const;
    bool CanEquip() const;
    void EquipWeapon(int32 WeaponIndex);

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;

    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;
        
    void SpawnWeapons();
    void AttachWeaponToSocket(AVDBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    
    void PlayAnimMontage(UAnimMontage* Animation);
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComp);
    void OnReloadFinished(USkeletalMeshComponent* MeshComp);

    bool CanReload() const;

    void OnClipEmpty(AVDBaseWeapon* AmmoEmptyWeapon);
    void ChangeClip();
};
