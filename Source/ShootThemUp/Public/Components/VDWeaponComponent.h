// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VDWeaponComponent.generated.h"

class AVDBaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API UVDWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UVDWeaponComponent();

    void StartFire();
    void StopFire();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<AVDBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponSocketName = "WeaponPoint";

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    AVDBaseWeapon* CurrentWeapon = nullptr;
    
    void SpawnWeapon();
};
