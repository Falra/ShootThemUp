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

bool UVDPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
    const auto Player = GetOwningPlayerPawn();
    if(!Player) return false;

    const auto WeaponComp = Player->FindComponentByClass<UVDWeaponComponent>();
    if(!WeaponComp) return false;

    return WeaponComp->GetWeaponUIData(UIData);
}
