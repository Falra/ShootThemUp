// Shoot Them Up Game. All Rights Reserved.


#include "Player/VDPlayerCharacter.h"

#include "VDWeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

AVDPlayerCharacter::AVDPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);
    
    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
    CameraCollisionComponent->SetupAttachment(CameraComponent);
    CameraCollisionComponent->SetSphereRadius(10.0f);
    CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void AVDPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(CameraCollisionComponent);
    CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AVDPlayerCharacter::OnCameraCollisionBeginOverlap);
    CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AVDPlayerCharacter::OnCameraCollisionEndOverlap);
}

void AVDPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);
    check(HealthComponent);
    check(WeaponComponent);
    check(GetCharacterMovement());
    check(GetMesh());

    PlayerInputComponent->BindAxis("MoveForward", this, &AVDPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AVDPlayerCharacter::MoveRight);

    PlayerInputComponent->BindAxis("LookUp", this, &AVDPlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &AVDPlayerCharacter::AddControllerYawInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AVDPlayerCharacter::Jump);

    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AVDPlayerCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &AVDPlayerCharacter::OnStopRunning);

    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AVDPlayerCharacter::OnStartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UVDWeaponComponent::StopFire);
    
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UVDWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UVDWeaponComponent::Reload);

    DECLARE_DELEGATE_OneParam(FZoomInputSignature, bool);
    PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Pressed, WeaponComponent, &UVDWeaponComponent::Zoom, true);
    PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Released, WeaponComponent, &UVDWeaponComponent::Zoom, false);
}

bool AVDPlayerCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

void AVDPlayerCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0.0f;
    if (Amount == 0.0f) return;
    AddMovementInput(GetActorForwardVector(), Amount);
    if (IsRunning() && WeaponComponent->IsFiring())
    {
        WeaponComponent->StopFire();
    }
}

void AVDPlayerCharacter::MoveRight(float Amount)
{
    if (Amount == 0.0f) return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void AVDPlayerCharacter::OnStartRunning()
{
    WantsToRun = true;
    if (IsRunning())
    {
        WeaponComponent->StopFire();
    }
}

void AVDPlayerCharacter::OnStopRunning()
{
    WantsToRun = false;
}

void AVDPlayerCharacter::OnStartFire()
{
    if (IsRunning()) return;
    WeaponComponent->StartFire();
}

void AVDPlayerCharacter::CheckCameraOverlap() const
{
    const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(HideMesh);

    TArray<USceneComponent*> MeshChildren;
    GetMesh()->GetChildrenComponents(true, MeshChildren);
    for(const auto MeshChild: MeshChildren)
    {
        const auto MeshChildGeometry = Cast<UPrimitiveComponent>(MeshChild);
        if(!MeshChildGeometry) continue;
        MeshChildGeometry->SetOwnerNoSee(HideMesh);
    }
}

void AVDPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
    CheckCameraOverlap();
}

void AVDPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
    CheckCameraOverlap();
}

void AVDPlayerCharacter::OnDeath()
{
    Super::OnDeath();
    
    if(Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}
