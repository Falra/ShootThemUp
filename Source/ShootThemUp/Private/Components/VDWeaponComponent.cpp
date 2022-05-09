// Shoot Them Up Game. All Rights Reserved.


#include "Components/VDWeaponComponent.h"
#include "Weapon/VDBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/VDEquipFinishedAnimNotify.h"
#include "Animations/VDReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

constexpr static int32 WeaponNum = 2;

UVDWeaponComponent::UVDWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UVDWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    checkf(WeaponData.Num() == WeaponNum, TEXT("Our character can hold only %i weapon items"), WeaponNum);
    
    CurrentWeaponIndex = 0;
    InitAnimations();
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void UVDWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (const auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();

    Super::EndPlay(EndPlayReason);
}

void UVDWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld()) return;

    for (auto OneWeaponData : WeaponData)
    {
        auto Weapon = GetWorld()->SpawnActor<AVDBaseWeapon>(OneWeaponData.WeaponClass);
        if(!Weapon) continue;
        Weapon->OnClipEmpty.AddUObject(this, &UVDWeaponComponent::OnClipEmpty);
        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);
        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void UVDWeaponComponent::StartFire()
{
    if(!CanFire()) return;
    CurrentWeapon->StartFire();
}

void UVDWeaponComponent::StopFire()
{
    if(!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void UVDWeaponComponent::NextWeapon()
{
    if(!CanEquip()) return;
    
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void UVDWeaponComponent::AttachWeaponToSocket(AVDBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if(!Weapon || !SceneComponent) return;
    
    const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UVDWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    if(WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
    {
        UE_LOG(LogWeaponComponent, Warning, TEXT("Invalid weapon index"));
        return;
    } 
    
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    if(CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }
    
    CurrentWeapon = Weapons[WeaponIndex];

    // CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
    const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data)
    {
        return Data.WeaponClass == CurrentWeapon->GetClass();
    });
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
    
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void UVDWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    Character->PlayAnimMontage(Animation);
}

void UVDWeaponComponent::InitAnimations()
{
    auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<UVDEquipFinishedAnimNotify>(EquipAnimMontage);
    if(EquipFinishedNotify)
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &UVDWeaponComponent::OnEquipFinished);
    }
    else
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify if forgotten to set"));
        checkNoEntry();
    }

    for(auto OneWeaponData : WeaponData)
    {
        auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<UVDReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
        if(!ReloadFinishedNotify)
        {
            UE_LOG(LogWeaponComponent, Error, TEXT("Reload anim notify if forgotten to set"));
            checkNoEntry();
        }
        ReloadFinishedNotify->OnNotified.AddUObject(this, &UVDWeaponComponent::OnReloadFinished);
    }
}

void UVDWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComp != Character->GetMesh()) return;

    EquipAnimInProgress = false;
}

void UVDWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComp != Character->GetMesh()) return;

    ReloadAnimInProgress = false;
}

bool UVDWeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress; 
}

bool UVDWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UVDWeaponComponent::CanReload() const
{
    return CurrentWeapon            //
           && !EquipAnimInProgress  //
           && !ReloadAnimInProgress //
           && CurrentWeapon->CanReload(); 
}

void UVDWeaponComponent::Reload()
{
    ChangeClip();
}

bool UVDWeaponComponent::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    if(CurrentWeapon)
    {
        UIData = CurrentWeapon->GetUIData();
        return true;
    }
    return false;
}

bool UVDWeaponComponent::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    if(CurrentWeapon)
    {
        AmmoData = CurrentWeapon->GetAmmoData();
        return true;
    }
    return false;
}

bool UVDWeaponComponent::TryToAddAmmo(const TSubclassOf<AVDBaseWeapon>& WeaponType, int32 ClipsAmount)
{
    for(const auto Weapon : Weapons)
    {
        if(Weapon && Weapon->IsA(WeaponType))
        {
            return Weapon->TryToAddAmmo(ClipsAmount);
        }
    }
    return false;
}

void UVDWeaponComponent::OnClipEmpty(AVDBaseWeapon* AmmoEmptyWeapon)
{
    if(!AmmoEmptyWeapon) return;
    
    if(CurrentWeapon == AmmoEmptyWeapon)
    {
        ChangeClip();
    }
    else
    {
        for(const auto Weapon : Weapons)
        {
            if (AmmoEmptyWeapon == Weapon)
            {
                Weapon->ChangeClip();
            }
        }
    }
}

void UVDWeaponComponent::ChangeClip()
{
    if(!CanReload()) return;

    CurrentWeapon->StopFire();
    CurrentWeapon->ChangeClip();
    
    ReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}
