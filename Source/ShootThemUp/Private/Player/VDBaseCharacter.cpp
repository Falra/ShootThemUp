// Shoot Them Up Game. All Rights Reserved.


#include "Player/VDBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/VDCharacterMovementComponent.h"

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
}

// Called when the game starts or when spawned
void AVDBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
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

void AVDBaseCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0.0f;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void AVDBaseCharacter::MoveRight(float Amount)
{
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