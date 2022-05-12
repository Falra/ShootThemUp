// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "VDNeedAmmoDecorator.generated.h"

class AVDBaseWeapon;

UCLASS()
class SHOOTTHEMUP_API UVDNeedAmmoDecorator : public UBTDecorator
{
    GENERATED_BODY()

public:
    UVDNeedAmmoDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<AVDBaseWeapon> WeaponType;
    
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
