// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VDPauseWidget.generated.h"

class UButton;

UCLASS()
class SHOOTTHEMUP_API UVDPauseWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ResumeGameButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnResumeGame();
};
