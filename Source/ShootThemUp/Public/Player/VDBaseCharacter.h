// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VDPlayerState.h"
#include "GameFramework/Character.h"
#include "VDBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UVDHealthComponent;
class UVDWeaponComponent;
class UTextRenderComponent;
class UAnimMontage;

UCLASS()
class SHOOTTHEMUP_API AVDBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AVDBaseCharacter(const FObjectInitializer& ObjInit);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UVDHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* HealthTextComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UVDWeaponComponent* WeaponComponent;
    
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    float LifeSpanOnDeath = 5.0f;
    
    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);
    
    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamage = FVector2D(10.0f, 100.f);

    UPROPERTY(EditDefaultsOnly, Category = "Material")
    FName MaterialColorName = "Paint Color";
    
    virtual void BeginPlay() override;

    virtual void OnDeath();

public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

    void SetPlayerColor(const FLinearColor& Color);

private:
    bool WantsToRun = false;
    bool IsMovingForward = false;

    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void OnStartRunning();
    void OnStopRunning();
    void OnStartFire();

    void OnHealthChanged(float NewHealth, float DeltaHealth);

    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);
};
