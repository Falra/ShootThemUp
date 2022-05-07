// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/VDLauncherWeapon.h"
#include "Weapon/VDProjectile.h"
#include "Kismet/GameplayStatics.h"

void AVDLauncherWeapon::StartFire()
{
    MakeShot();
}

void AVDLauncherWeapon::MakeShot()
{
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
    // TODO: Set projectile params
    UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}
