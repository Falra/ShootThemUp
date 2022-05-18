// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/VDRifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Components/VDWeaponFXComponent.h"
#include "Engine/World.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

AVDRifleWeapon::AVDRifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<UVDWeaponFXComponent>("WeaponFXComponent");
}

void AVDRifleWeapon::StartFire()
{
    Super::StartFire();
    InitFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AVDRifleWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
}

void AVDRifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetFXActive(false);
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

    FVector TraceFXEnd = TraceEnd;
    if(HitResult.bBlockingHit)
    {
        TraceFXEnd = HitResult.ImpactPoint;
        MakeDamage(HitResult);
        WeaponFXComponent->PlayImpactFX(HitResult);
    }
    SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
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

    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetController(), this);
}

void AVDRifleWeapon::InitFX()
{
    if(!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }

    if(!FireAudioComponent)
    {
        FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
    }
    
    SetFXActive(true);
}

void AVDRifleWeapon::SetFXActive(bool IsActive)
{
    if(MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!IsActive);
        MuzzleFXComponent->SetVisibility(IsActive, true);
    }

    if(FireAudioComponent)
    {
        FireAudioComponent->SetPaused(!IsActive);
    }
}

void AVDRifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
    if(TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}

AController* AVDRifleWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}