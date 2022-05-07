// Shoot Them Up Game. All Rights Reserved.


#include "Components/VDWeaponComponent.h"
#include "Weapon/VDBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/VDEquipFinishedAnimNotify.h"
#include "Animations/VDReloadFinishedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

UVDWeaponComponent::UVDWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UVDWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

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

void UVDWeaponComponent::Reload()
{
    if(!CanReload()) return;
    ReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
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
    auto EquipFinishedNotify = FindNotifyByClass<UVDEquipFinishedAnimNotify>(EquipAnimMontage);
    if(EquipFinishedNotify)
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &UVDWeaponComponent::OnEquipFinished);
    }

    for(auto OneWeaponData : WeaponData)
    {
        auto ReloadFinishedNotify = FindNotifyByClass<UVDReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
        if(!ReloadFinishedNotify) continue;
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
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress; 
}
