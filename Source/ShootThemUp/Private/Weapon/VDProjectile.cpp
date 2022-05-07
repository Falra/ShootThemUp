// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/VDProjectile.h"
#include "Components/SphereComponent.h"

AVDProjectile::AVDProjectile()
{
    PrimaryActorTick.bCanEverTick = false;
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    SetRootComponent(CollisionComponent);
}

void AVDProjectile::BeginPlay()
{
    Super::BeginPlay();
}
