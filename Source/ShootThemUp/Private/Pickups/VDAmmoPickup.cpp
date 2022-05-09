// Shoot Them Up Game. All Rights Reserved.


#include "Pickups/VDAmmoPickup.h"
#include "Components/VDHealthComponent.h"
#include "Components/VDWeaponComponent.h"
#include "VDUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All)

bool AVDAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = VDUtils::GetVDPlayerComponent<UVDHealthComponent>(PlayerPawn);
    if(!HealthComponent || HealthComponent->IsDead()) return false;

    const auto WeaponComponent = VDUtils::GetVDPlayerComponent<UVDWeaponComponent>(PlayerPawn);
    if(!WeaponComponent) return false;

    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
