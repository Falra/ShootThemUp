// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VDPlayerState.h"
#include "GameFramework/Character.h"
#include "VDBaseCharacter.generated.h"

class UVDHealthComponent;
class UVDWeaponComponent;
class UAnimMontage;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API AVDBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AVDBaseCharacter(const FObjectInitializer& ObjInit);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UVDHealthComponent* HealthComponent;

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
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* DeathSound;
        
    virtual void BeginPlay() override;

    virtual void OnDeath();

    virtual void OnHealthChanged(float NewHealth, float DeltaHealth);

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    virtual bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

    void SetPlayerColor(const FLinearColor& Color);

private:
    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);
};
