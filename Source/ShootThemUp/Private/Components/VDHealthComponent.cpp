// Shoot Them Up Game. All Rights Reserved.


#include "Components/VDHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UVDHealthComponent::UVDHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UVDHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;

    AActor* ComponentOwner = GetOwner();
    if(ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UVDHealthComponent::OnTakeAnyDamage);
    }

}

void UVDHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser)
{
    if(Damage <= 0.0f || IsDead()) return;
    
    Health = FMath::Clamp(Health - Damage, 0.0f , MaxHealth);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}
