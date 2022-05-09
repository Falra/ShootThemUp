// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VDBasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API AVDBasePickup : public AActor
{
    GENERATED_BODY()

public:
    AVDBasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;
    
    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    
public:
    virtual void Tick(float DeltaTime) override;
};
