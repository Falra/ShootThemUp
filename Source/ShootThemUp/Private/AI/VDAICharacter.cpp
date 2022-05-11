// Shoot Them Up Game. All Rights Reserved.


#include "AI/VDAICharacter.h"
#include "AI/VDAIController.h"

AVDAICharacter::AVDAICharacter(const FObjectInitializer& ObjInit):Super(ObjInit)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AVDAIController::StaticClass();
}
