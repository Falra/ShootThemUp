// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VDCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "VDGameOverWidget.generated.h"

class UVerticalBox;

UCLASS()
class SHOOTTHEMUP_API UVDGameOverWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

private:
    void OnMatchStateChanged(EVDMatchState State);
    void UpdatePlayerStat();
};
