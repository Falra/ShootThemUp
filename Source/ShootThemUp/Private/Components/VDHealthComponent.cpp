// Shoot Them Up Game. All Rights Reserved.


#include "Components/VDHealthComponent.h"
#include "Dev/VDFireDamageType.h"
#include "Dev/VDIceDamageType.h"

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
    Health -= Damage;

    UE_LOG(LogHealthComponent, Display, TEXT("Damage: %f"), Damage);

    if(DamageType)
    {
        if(DamageType->IsA<UVDFireDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("Fire"));
        } else if(DamageType->IsA<UVDIceDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("Ice"));
        }
    }
}