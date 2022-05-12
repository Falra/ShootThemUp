// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "VDHealthPercentDecorator.generated.h"

UCLASS()
class SHOOTTHEMUP_API UVDHealthPercentDecorator : public UBTDecorator
{
    GENERATED_BODY()

public:
    UVDHealthPercentDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float HealthPercent = 0.6f;
    
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
