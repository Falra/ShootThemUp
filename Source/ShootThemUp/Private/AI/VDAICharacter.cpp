// Shoot Them Up Game. All Rights Reserved.


#include "AI/VDAICharacter.h"
#include "AI/VDAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/VDAIWeaponComponent.h"
#include "BrainComponent.h"

AVDAICharacter::AVDAICharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UVDAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = AVDAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if(GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }
}

void AVDAICharacter::OnDeath()
{
    Super::OnDeath();

    const auto VDController = Cast<AAIController>(Controller);
    if(VDController && VDController->BrainComponent)
    {
        VDController->BrainComponent->Cleanup();
    }
}
