// Shoot Them Up Game. All Rights Reserved.


#include "Components/VDCharacterMovementComponent.h"
#include "Player/VDBaseCharacter.h"

float UVDCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const AVDBaseCharacter* Player = Cast<AVDBaseCharacter>(GetPawnOwner());
    return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
