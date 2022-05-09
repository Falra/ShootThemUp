// Shoot Them Up Game. All Rights Reserved.


#include "Pickups/VDAmmoPickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All)

bool AVDAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    UE_LOG(LogAmmoPickup, Display, TEXT("Ammo was taken"));
    return true;
}
