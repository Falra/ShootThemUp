// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "VDAIController.generated.h"

class UVDAIPerceptionComponent;
class UVDRespawnComponent;

UCLASS()
class SHOOTTHEMUP_API AVDAIController : public AAIController
{
    GENERATED_BODY()

public:
    AVDAIController();
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UVDAIPerceptionComponent* VDAIPerceptionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UVDRespawnComponent* RespawnComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "EnemyActor";
    
    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaSeconds) override;

private:
    AActor* GetFocusOnActor() const;
};
