// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VDCoreTypes.h"
#include "UI/VDBaseWidget.h"
#include "VDGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SHOOTTHEMUP_API UVDGameOverWidget : public UVDBaseWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetLevelButton;

    virtual void NativeOnInitialized() override;
    
private:
    void OnMatchStateChanged(EVDMatchState State);
    void UpdatePlayerStat();

    UFUNCTION()
    void OnResetLevel();
};
