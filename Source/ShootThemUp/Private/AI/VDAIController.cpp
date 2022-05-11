// Shoot Them Up Game. All Rights Reserved.


#include "AI/VDAIController.h"
#include "AI/VDAICharacter.h"

void AVDAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto VDCharacter = Cast<AVDAICharacter>(InPawn);
    if(VDCharacter)
    {
        RunBehaviorTree(VDCharacter->BehaviorTreeAsset);
    }
}
