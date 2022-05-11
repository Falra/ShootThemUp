// Shoot Them Up Game. All Rights Reserved.


#include "AI/VDAIController.h"
#include "AI/VDAICharacter.h"
#include "Components/VDAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

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

void AVDAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    const auto AimActor = GetFocusOnActor();
    SetFocus(AimActor);
}

AActor* AVDAIController::GetFocusOnActor() const
{
    if(!GetBlackboardComponent()) return nullptr;

    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
