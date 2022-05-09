// Shoot Them Up Game. All Rights Reserved.


#include "Pickups/VDBasePickup.h"

#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All)

AVDBasePickup::AVDBasePickup()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
    
}

void AVDBasePickup::BeginPlay()
{
    Super::BeginPlay();
}

void AVDBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    UE_LOG(LogBasePickup, Display, TEXT("Pickup overlap"));
    Destroy();
}

void AVDBasePickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
