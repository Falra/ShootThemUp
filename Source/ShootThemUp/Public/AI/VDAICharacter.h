// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/VDBaseCharacter.h"
#include "VDAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SHOOTTHEMUP_API AVDAICharacter : public AVDBaseCharacter
{
    GENERATED_BODY()

public:
    AVDAICharacter(const FObjectInitializer& ObjInit);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;
};
