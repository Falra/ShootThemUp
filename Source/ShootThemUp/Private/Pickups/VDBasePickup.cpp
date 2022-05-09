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

    check(CollisionComponent);
}

void AVDBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if(GivePickupTo(Pawn))
    {
        PickupWasTaken();
    }
}

void AVDBasePickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AVDBasePickup::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void AVDBasePickup::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    GetRootComponent()->SetVisibility(false, true);

    FTimerHandle RespawnTimerHandle;
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AVDBasePickup::Respawn, RespawnTime);
}

void AVDBasePickup::Respawn()
{
    GetRootComponent()->SetVisibility(true, true);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}
