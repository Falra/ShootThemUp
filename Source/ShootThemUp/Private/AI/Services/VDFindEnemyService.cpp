// Shoot Them Up Game. All Rights Reserved.


#include "AI/Services/VDFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "VDUtils.h"
#include "Components/VDAIPerceptionComponent.h"

UVDFindEnemyService::UVDFindEnemyService()
{
    NodeName = "Find Enemy";
}

void UVDFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if(Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = VDUtils::GetVDPlayerComponent<UVDAIPerceptionComponent>(Controller);
        if(PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
