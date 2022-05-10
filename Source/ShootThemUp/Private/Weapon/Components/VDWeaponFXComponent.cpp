// Shoot Them Up Game. All Rights Reserved.


#include "Weapon/Components/VDWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

UVDWeaponFXComponent::UVDWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UVDWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
    auto ImpactData = DefaultImpactData;
    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap[PhysMat];
        }
    }

    // Niagara
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), //
        ImpactData.NiagaraEffect,                              //
        Hit.ImpactPoint,                                       //
        Hit.ImpactNormal.Rotation());

    const FDecalData DecalData = ImpactData.DecalData;

    // Decal
    auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), //
        DecalData.Material,                                       //
        DecalData.Size,                                           //
        Hit.ImpactPoint,                                                     //
        Hit.ImpactNormal.Rotation());
    if(DecalComponent)
    {
        DecalComponent->SetFadeOut(DecalData.LifeTime, DecalData.FadeOutTime);
    }
}
