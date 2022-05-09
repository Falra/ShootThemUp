// Shoot Them Up Game. All Rights Reserved.


#include "Components/VDHealthComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UVDHealthComponent::UVDHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

bool UVDHealthComponent::TryToAddHealth(float HealthAmount)
{
    if(IsDead() || IsHealthFull()) return false;

    SetHealth(Health + HealthAmount);
    return true;
}

bool UVDHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

void UVDHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0);

    SetHealth(MaxHealth);
    
    AActor* ComponentOwner = GetOwner();
    if(ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UVDHealthComponent::OnTakeAnyDamage);
    }

}

void UVDHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser)
{
    if(Damage <= 0.0f || IsDead() || !GetWorld() ) return;
    
    SetHealth(Health - Damage);

    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    
    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (AutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UVDHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
    }
}

void UVDHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);
    
    if(IsHealthFull() && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void UVDHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f , MaxHealth);
    OnHealthChanged.Broadcast(Health);
    
}
