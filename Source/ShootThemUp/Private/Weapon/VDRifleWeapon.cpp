// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/VDRifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Components/VDWeaponFXComponent.h"
#include "Engine/World.h"
#include "NiagaraComponent.h"

AVDRifleWeapon::AVDRifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<UVDWeaponFXComponent>("WeaponFXComponent");
}

void AVDRifleWeapon::StartFire()
{
    Super::StartFire();
    InitMuzzleFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AVDRifleWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
}

void AVDRifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetMuzzleFXVisibility(false);
}

void AVDRifleWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponFXComponent);
}

void AVDRifleWeapon::MakeShot()
{
    if(!GetWorld() || IsAmmoEmpty())
    {
        StopFire();
        return;
    };

    FVector TraceStart, TraceEnd;
    if(!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    };
    
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector MuzzleLocation = GetMuzzleWorldLocation();
    if(HitResult.bBlockingHit)
    {
        MakeDamage(HitResult);
        //DrawDebugLine(GetWorld(), MuzzleLocation, HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
        WeaponFXComponent->PlayImpactFX(HitResult);
    }
    else
    {
        DrawDebugLine(GetWorld(), MuzzleLocation, TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
    }

    DecreaseAmmo();
}

bool AVDRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;
    
    TraceStart = ViewLocation;
    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void AVDRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if(!DamagedActor) return;

    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPLayerController(), this);
}

void AVDRifleWeapon::InitMuzzleFX()
{
    if(!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }
    SetMuzzleFXVisibility(true);
}

void AVDRifleWeapon::SetMuzzleFXVisibility(bool Visible)
{
    if(MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!Visible);
        MuzzleFXComponent->SetVisibility(Visible, true);
    }
}
