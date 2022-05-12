// Shoot Them Up Game. All Rights Reserved.


#include "AI/Decorators/VDHealthPercentDecorator.h"
#include "AIController.h"
#include "VDUtils.h"
#include "Components/VDHealthComponent.h"

UVDHealthPercentDecorator::UVDHealthPercentDecorator()
{
    NodeName = "Health Percent";
}

bool UVDHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(!Controller) return false;

    const auto HealthComponent = VDUtils::GetVDPlayerComponent<UVDHealthComponent>(Controller->GetPawn());
    if(!HealthComponent || HealthComponent->IsDead()) return false;

    return HealthComponent->GetHealthPercent() <= HealthPercent;
}
