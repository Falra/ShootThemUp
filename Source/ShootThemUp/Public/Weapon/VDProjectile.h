// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VDProjectile.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API AVDProjectile : public AActor
{
    GENERATED_BODY()

public:
    AVDProjectile();

protected:
    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* CollisionComponent;
    
    virtual void BeginPlay() override;
};
