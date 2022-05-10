// Shoot Them Up Game. All Rights Reserved.


#include "UI/VDPlayerHUDWidget.h"
#include "Components/VDHealthComponent.h"
#include "Components/VDWeaponComponent.h"
#include "VDUtils.h"

float UVDPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComp = VDUtils::GetVDPlayerComponent<UVDHealthComponent>(GetOwningPlayerPawn());
    if(!HealthComp) return 0.0f;
    
    return HealthComp->GetHealthPercent();
}

bool UVDPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComp = VDUtils::GetVDPlayerComponent<UVDWeaponComponent>(GetOwningPlayerPawn());
    if(!WeaponComp) return false;

    return WeaponComp->GetCurrentWeaponUIData(UIData);
}

bool UVDPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto WeaponComp = VDUtils::GetVDPlayerComponent<UVDWeaponComponent>(GetOwningPlayerPawn());
    if(!WeaponComp) return false;

    return WeaponComp->GetCurrentWeaponAmmoData(AmmoData);
}

bool UVDPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComp = VDUtils::GetVDPlayerComponent<UVDHealthComponent>(GetOwningPlayerPawn());;
    return HealthComp && !HealthComp->IsDead();
    
}

bool UVDPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}