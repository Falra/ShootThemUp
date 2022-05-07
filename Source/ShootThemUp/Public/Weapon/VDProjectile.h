// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VDProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTTHEMUP_API AVDProjectile : public AActor
{
    GENERATED_BODY()

public:
    AVDProjectile();
    void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; };
    
protected:
    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    UProjectileMovementComponent* MovementComponent;
    
    virtual void BeginPlay() override;
private:
    FVector ShotDirection;
};
