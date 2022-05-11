// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "VDAIController.generated.h"

class UVDAIPerceptionComponent;

UCLASS()
class SHOOTTHEMUP_API AVDAIController : public AAIController
{
    GENERATED_BODY()

public:
    AVDAIController();
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UVDAIPerceptionComponent* VDAIPerceptionComponent;
    
    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaSeconds) override;
};
