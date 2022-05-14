// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/VDBaseCharacter.h"
#include "VDPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API AVDPlayerCharacter : public AVDBaseCharacter
{
    GENERATED_BODY()

public:
    AVDPlayerCharacter(const FObjectInitializer& ObjInit);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USphereComponent* CameraCollisionComponent;
    
    virtual void OnDeath() override;
    virtual void BeginPlay() override;

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual bool IsRunning() const override;

private:
    bool WantsToRun = false;
    bool IsMovingForward = false;

    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void OnStartRunning();
    void OnStopRunning();
    void OnStartFire();

    void CheckCameraOverlap();

    UFUNCTION()
    void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);
    UFUNCTION()
    void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex);
    
};
