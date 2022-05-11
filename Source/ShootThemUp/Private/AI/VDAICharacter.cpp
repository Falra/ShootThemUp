// Shoot Them Up Game. All Rights Reserved.


#include "AI/VDAICharacter.h"
#include "AI/VDAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/VDAIWeaponComponent.h"

AVDAICharacter::AVDAICharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UVDAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AVDAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if(GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }
}
