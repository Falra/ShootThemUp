// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/VDBaseCharacter.h"
#include "VDAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class SHOOTTHEMUP_API AVDAICharacter : public AVDBaseCharacter
{
    GENERATED_BODY()

public:
    AVDAICharacter(const FObjectInitializer& ObjInit);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

    virtual void Tick(float DeltaSeconds) override;
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UWidgetComponent* HealthWidgetComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    float HealthVisibilityDistance = 1000.0f;
    
    virtual void BeginPlay() override;
    virtual void OnDeath() override;
    virtual void OnHealthChanged(float NewHealth, float DeltaHealth) override;

private:
    void UpdateHealthWidgetVisibility();
};
