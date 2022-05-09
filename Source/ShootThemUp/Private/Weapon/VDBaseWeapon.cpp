// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/VDBaseWeapon.h"

#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

AVDBaseWeapon::AVDBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void AVDBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponMesh);
    checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count couldn't be less or equal 0"));
    checkf(DefaultAmmo.Clips > 0, TEXT("Clips count couldn't be less or equal 0"));
    
    CurrentAmmo = DefaultAmmo;
}

void AVDBaseWeapon::StartFire()
{
}

void AVDBaseWeapon::StopFire()
{
}

void AVDBaseWeapon::MakeShot()
{
}

APlayerController* AVDBaseWeapon::GetPLayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if(!Player) return nullptr;

    return Player->GetController<APlayerController>();
}

bool AVDBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto Controller = GetPLayerController();
    if(!Controller) return false;

    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return  true;
}

FVector AVDBaseWeapon::GetMuzzleWorldLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool AVDBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;
    
    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void AVDBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{
    if(!GetWorld()) return;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void AVDBaseWeapon::DecreaseAmmo()
{
    if(CurrentAmmo.Bullets == 0)
    {
        UE_LOG(LogBaseWeapon, Warning, TEXT("No more bullets"));
        return;
    }
    
    CurrentAmmo.Bullets--;

    if(IsClipEmpty() && !IsAmmoEmpty())
    {
        StopFire();
        OnClipEmpty.Broadcast(this);
    }
}

bool AVDBaseWeapon::IsAmmoEmpty() const
{
    return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool AVDBaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

bool AVDBaseWeapon::IsAmmoFull() const
{
    return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

void AVDBaseWeapon::ChangeClip()
{
    if(!CurrentAmmo.Infinite)
    {
        if(CurrentAmmo.Clips == 0)
        {
            UE_LOG(LogBaseWeapon, Warning, TEXT("No more clips"));
            return;
        }
        CurrentAmmo.Clips--;
    }
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    UE_LOG(LogBaseWeapon, Display, TEXT("Change Clip"));
}

bool AVDBaseWeapon::CanReload() const
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

bool AVDBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
    if(CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;

    if(IsAmmoEmpty())
    {
        CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
        OnClipEmpty.Broadcast(this);
    }
    else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
    {
        const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
        if(DefaultAmmo.Clips - NextClipsAmount >= 0)
        {
            CurrentAmmo.Clips = NextClipsAmount;
        }
        else
        {
            CurrentAmmo.Clips = DefaultAmmo.Clips;
            CurrentAmmo.Bullets = DefaultAmmo.Bullets;
        }
    }
    else
    {
        CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    }

    return true;
}

void AVDBaseWeapon::LogAmmo()
{
    FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
    AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
    UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}
