// Shoot Them Up Game. All Rights Reserved.


#include "Player/VDBaseCharacter.h"

#include "Components/VDHealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/VDCharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

// Sets default values
AVDBaseCharacter::AVDBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UVDCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<UVDHealthComponent>("HealthComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AVDBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &AVDBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &AVDBaseCharacter::OnHealthChanged);
}

// Called every frame
void AVDBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AVDBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AVDBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AVDBaseCharacter::MoveRight);

    PlayerInputComponent->BindAxis("LookUp", this, &AVDBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &AVDBaseCharacter::AddControllerYawInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AVDBaseCharacter::Jump);

    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AVDBaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &AVDBaseCharacter::OnStopRunning);
}

bool AVDBaseCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
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

void AVDBaseCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0.0f;
    if (Amount == 0.0f) return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void AVDBaseCharacter::MoveRight(float Amount)
{
    if (Amount == 0.0f) return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void AVDBaseCharacter::OnStartRunning()
{
    WantsToRun = true;
}

void AVDBaseCharacter::OnStopRunning()
{
    WantsToRun = false;
}

void AVDBaseCharacter::OnDeath()
{
    UE_LOG(BaseCharacterLog, Display, TEXT("YOU DEAD!!!"));

    PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();

    SetLifeSpan(5.0f);
}

void AVDBaseCharacter::OnHealthChanged(float NewHealth)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), NewHealth)));
}
