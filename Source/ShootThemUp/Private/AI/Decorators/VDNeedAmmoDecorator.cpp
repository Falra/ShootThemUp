// Shoot Them Up Game. All Rights Reserved.


#include "AI/Decorators/VDNeedAmmoDecorator.h"
#include "AIController.h"
#include "VDUtils.h"
#include "Components/VDWeaponComponent.h"

UVDNeedAmmoDecorator::UVDNeedAmmoDecorator()
{
    NodeName = "Need Ammo";
}

bool UVDNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(!Controller) return false;

    const auto WeaponComponent = VDUtils::GetVDPlayerComponent<UVDWeaponComponent>(Controller->GetPawn());
    if(!WeaponComponent) return false;

    return WeaponComponent->NeedAmmo(WeaponType);
}
