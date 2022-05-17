// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VDCoreTypes.h"
#include "VDGameHUD.generated.h"

class UVDBaseWidget;

UCLASS()
class SHOOTTHEMUP_API AVDGameHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

    virtual void BeginPlay() override;;
    
private:
    UPROPERTY()
    TMap<EVDMatchState, UVDBaseWidget*> GameWidgets;

    UPROPERTY()
    UVDBaseWidget* CurrentWidget = nullptr;
    
    void DrawCrossHair();
    void OnMatchStateChanged(EVDMatchState MatchState);
};
