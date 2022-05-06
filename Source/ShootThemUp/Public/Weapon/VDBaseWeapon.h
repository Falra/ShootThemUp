// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VDBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SHOOTTHEMUP_API AVDBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    AVDBaseWeapon();

    virtual void Fire();
    
protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleFlashSocket";

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TraceMaxDistance = 1500.0f;
    
    virtual void BeginPlay() override;

    void MakeShot();

    APlayerController* GetPLayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;
    bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
};
