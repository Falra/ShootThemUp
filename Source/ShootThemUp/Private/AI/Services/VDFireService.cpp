// Shoot Them Up Game. All Rights Reserved.


#include "AI/Services/VDFireService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/VDWeaponComponent.h"
#include "VDUtils.h"

UVDFireService::UVDFireService()
{
    NodeName = "Fire";
}

void UVDFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName); 
    if(Controller)
    {
        const auto WeaponComponent = VDUtils::GetVDPlayerComponent<UVDWeaponComponent>(Controller->GetPawn());
        if(WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
