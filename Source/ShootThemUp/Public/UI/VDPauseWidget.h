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

public:
    virtual bool Initialize() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ResumeGameButton;

private:
    UFUNCTION()
    void OnResumeGame();
};
