// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/Components/VDWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"

UVDWeaponFXComponent::UVDWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UVDWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
