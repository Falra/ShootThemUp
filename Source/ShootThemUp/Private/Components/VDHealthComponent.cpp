// Shoot Them Up Game. All Rights Reserved.


#include "Components/VDHealthComponent.h"

UVDHealthComponent::UVDHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UVDHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;
}
