// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VDGameHUD.generated.h"

UCLASS()
class SHOOTTHEMUP_API AVDGameHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    virtual void BeginPlay() override;;
    
private:
    void DrawCrossHair();
};
