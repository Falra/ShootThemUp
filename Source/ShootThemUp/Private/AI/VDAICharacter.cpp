// Shoot Them Up Game. All Rights Reserved.


#include "AI/VDAICharacter.h"
#include "AI/VDAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/VDAIWeaponComponent.h"
#include "Components/WidgetComponent.h"
#include "BrainComponent.h"
#include "UI/VDHealthBarWidget.h"
#include "Components/VDHealthComponent.h"

AVDAICharacter::AVDAICharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UVDAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = AVDAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if(GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void AVDAICharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    UpdateHealthWidgetVisibility();
}

void AVDAICharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthWidgetComponent);
}

void AVDAICharacter::OnDeath()
{
    Super::OnDeath();

    const auto VDController = Cast<AAIController>(Controller);
    if(VDController && VDController->BrainComponent)
    {
        VDController->BrainComponent->Cleanup();
    }
}

void AVDAICharacter::OnHealthChanged(float NewHealth, float DeltaHealth)
{
    Super::OnHealthChanged(NewHealth, DeltaHealth);

    const auto HealthBarWidget = Cast<UVDHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if(!HealthBarWidget) return;

    HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void AVDAICharacter::UpdateHealthWidgetVisibility()
{
    if (!GetWorld() ||                                                 //
        !GetWorld()->GetFirstPlayerController() ||                     //
        !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()) //
        return;
    
    const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
    const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
    HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance ? true : false, true);
}
