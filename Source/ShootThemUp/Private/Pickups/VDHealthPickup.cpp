// Shoot Them Up Game. All Rights Reserved.


#include "Pickups/VDHealthPickup.h"
#include "Components/VDHealthComponent.h"
#include "VDUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All)

bool AVDHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = VDUtils::GetVDPlayerComponent<UVDHealthComponent>(PlayerPawn);
    if(!HealthComponent) return false;
    
    return HealthComponent->TryToAddHealth(HealthAmount);
}
