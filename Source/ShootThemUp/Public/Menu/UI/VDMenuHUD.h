// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VDMenuHUD.generated.h"

UCLASS()
class SHOOTTHEMUP_API AVDMenuHUD : public AHUD
{
    GENERATED_BODY()
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;
    
    virtual void BeginPlay() override;
};
