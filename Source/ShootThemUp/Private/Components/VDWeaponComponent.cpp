// Shoot Them Up Game. All Rights Reserved.


#include "Components/VDWeaponComponent.h"
#include "Weapon/VDBaseWeapon.h"
#include "GameFramework/Character.h"

UVDWeaponComponent::UVDWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UVDWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    SpawnWeapon();
}


void UVDWeaponComponent::SpawnWeapon()
{
    if(!GetWorld()) return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    const auto Weapon = GetWorld()->SpawnActor<AVDBaseWeapon>(WeaponClass);
    if(!Weapon) return;
    
    const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    WeaponSocketName = "WeaponPoint";
    Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponSocketName);
}