// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/VDBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

AVDBaseWeapon::AVDBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void AVDBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}
