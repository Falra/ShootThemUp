// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VDGameDataWidget.generated.h"

class AVDGameModeBase;
class AVDPlayerState;

UCLASS()
class SHOOTTHEMUP_API UVDGameDataWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetCurrentRoundNum() const;
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetTotalRoundsNum() const;
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetRoundSecondsRemaining() const;

private:
    AVDGameModeBase* GetGameMode() const;
    AVDPlayerState* GetPlayerState() const;
};
