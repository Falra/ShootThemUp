// Shoot Them Up Game. All Rights Reserved.


#include "UI/VDPlayerHUDWidget.h"
#include "Components/VDHealthComponent.h"
#include "Components/VDWeaponComponent.h"

float UVDPlayerHUDWidget::GetHealthPercent() const
{
    const auto Player = GetOwningPlayerPawn();
    if(!Player) return 0.0f;

    const auto HealthComp = Player->FindComponentByClass<UVDHealthComponent>();
    if(!HealthComp) return 0.0f;
    
    return HealthComp->GetHealthPercent();
}

bool UVDPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComp = GetWeaponComponent();
    if(!WeaponComp) return false;

    return WeaponComp->GetCurrentWeaponUIData(UIData);
}

bool UVDPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto WeaponComp = GetWeaponComponent();
    if(!WeaponComp) return false;

    return WeaponComp->GetCurrentWeaponAmmoData(AmmoData);
}

UVDWeaponComponent* UVDPlayerHUDWidget::GetWeaponComponent() const
{
    const auto Player = GetOwningPlayerPawn();
    if(!Player) return nullptr;

    const auto WeaponComp = Player->FindComponentByClass<UVDWeaponComponent>();
    return WeaponComp;
}
