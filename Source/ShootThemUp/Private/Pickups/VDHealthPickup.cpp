// Shoot Them Up Game. All Rights Reserved.


#include "Pickups/VDHealthPickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All)

bool AVDHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    UE_LOG(LogHealthPickup, Display, TEXT("Health was taken"));
    return true;
}
