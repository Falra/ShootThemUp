// Shoot Them Up Game. All Rights Reserved.


#include "AI/Services/VDChangeWeaponService.h"
#include "Components/VDWeaponComponent.h"
#include "AIController.h"
#include "VDUtils.h"

UVDChangeWeaponService::UVDChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void UVDChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(Controller)
    {
        const auto WeaponComponent = VDUtils::GetVDPlayerComponent<UVDWeaponComponent>(Controller->GetPawn());
        if(WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
        {
            WeaponComponent->NextWeapon(); 
        }
    }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
