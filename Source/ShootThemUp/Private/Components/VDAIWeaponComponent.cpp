// Shoot Them Up Game. All Rights Reserved.


#include "Components/VDAIWeaponComponent.h"
#include "Weapon/VDBaseWeapon.h"

void UVDAIWeaponComponent::StartFire()
{
    if(!CanFire()) return;

    if(CurrentWeapon->IsAmmoEmpty())
    {
        NextWeapon();
    }
    else
    {
        CurrentWeapon->StartFire();
    }
}

void UVDAIWeaponComponent::NextWeapon()
{
    if(!CanEquip()) return;
    int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    while (NextIndex != CurrentWeaponIndex)
    {
        if(!Weapons[NextIndex]->IsAmmoEmpty()) break;
        NextIndex = (NextIndex + 1) % Weapons.Num();
    }
    if(CurrentWeaponIndex != NextIndex)
    {
        CurrentWeaponIndex = NextIndex;
        EquipWeapon(CurrentWeaponIndex);
    }
}
