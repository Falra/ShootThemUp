// Shoot Them Up Game. All Rights Reserved.


#include "Components/VDAIPerceptionComponent.h"
#include "AIController.h"
#include "VDUtils.h"
#include "Components/VDHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* UVDAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PerceiveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
    if(PerceiveActors.Num()  == 0) return nullptr;

    const auto Controller = Cast<AAIController>(GetOwner());
    if(!Controller) return nullptr;

    const auto Pawn = Controller->GetPawn();
    if(!Pawn) return nullptr;

    float BestDistance = MAX_FLT;
    AActor* BestPawn = nullptr;
    for(const auto PerceiveActor : PerceiveActors)
    {
        const auto HealthComponent = VDUtils::GetVDPlayerComponent<UVDHealthComponent>(PerceiveActor);
        const auto PerceivePawn = Cast<APawn>(PerceiveActor);
        const auto AreEnemies = PerceivePawn && VDUtils::AreEnemies(Controller, PerceivePawn->Controller);
        
        if(HealthComponent && !HealthComponent->IsDead() && AreEnemies)
        {
            const auto CurrentDistance = (PerceiveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if(CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestPawn = PerceiveActor;
            }
        }
    }
    
    return BestPawn;
}
