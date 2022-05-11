// Shoot Them Up Game. All Rights Reserved.


#include "AI/VDAIController.h"
#include "AI/VDAICharacter.h"
#include "Components/VDAIPerceptionComponent.h"

AVDAIController::AVDAIController()
{
    VDAIPerceptionComponent = CreateDefaultSubobject<UVDAIPerceptionComponent>("VDAIPerceptionComponent");
    SetPerceptionComponent(*VDAIPerceptionComponent);
}

void AVDAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto VDCharacter = Cast<AVDAICharacter>(InPawn);
    if(VDCharacter)
    {
        RunBehaviorTree(VDCharacter->BehaviorTreeAsset);
    }
}
