// Shoot Them Up Game. All Rights Reserved.


#include "Player/VDBaseCharacter.h"

#include "Components/VDWeaponComponent.h"
#include "Components/VDHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/VDCharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

AVDBaseCharacter::AVDBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UVDCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;
    HealthComponent = CreateDefaultSubobject<UVDHealthComponent>("HealthComponent");
    WeaponComponent = CreateDefaultSubobject<UVDWeaponComponent>("WeaponComponent");
}

void AVDBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(WeaponComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnDeath.AddUObject(this, &AVDBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &AVDBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &AVDBaseCharacter::OnGroundLanded);
}

void AVDBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AVDBaseCharacter::IsRunning() const
{
    return false;
}

float AVDBaseCharacter::GetMovementDirection() const
{
    if(GetVelocity().IsZero()) return  0.0f;
    
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto RadiansToDegrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? RadiansToDegrees : RadiansToDegrees * FMath::Sign(CrossProduct.Z);
}

void AVDBaseCharacter::SetPlayerColor(const FLinearColor& Color)
{
    const auto MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if(!MaterialInstance) return;

    MaterialInstance->SetVectorParameterValue(MaterialColorName, Color);
}

void AVDBaseCharacter::OnDeath()
{
    UE_LOG(BaseCharacterLog, Display, TEXT("YOU DEAD!!!"));

    //PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();

    SetLifeSpan(LifeSpanOnDeath);

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();
    WeaponComponent->Zoom(false);

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

void AVDBaseCharacter::OnHealthChanged(float NewHealth, float DeltaHealth)
{
}

void AVDBaseCharacter::TurnOff()
{
    WeaponComponent->StopFire();
    WeaponComponent->Zoom(false);
    Super::TurnOff();
}

void AVDBaseCharacter::Reset()
{
    WeaponComponent->StopFire();
    WeaponComponent->Zoom(false);
    Super::Reset();
}

void AVDBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    const auto FallVelocityZ = -GetVelocity().Z;
    UE_LOG(BaseCharacterLog, Display, TEXT("On Landed: %f"), FallVelocityZ);

    if(FallVelocityZ < LandedDamageVelocity.X) return;

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    UE_LOG(BaseCharacterLog, Display, TEXT("Final damage: %f"), FinalDamage);

    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}
