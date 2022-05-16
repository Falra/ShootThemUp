// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VDPlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class SHOOTTHEMUP_API UVDPlayerStatRowWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetPlayerName(const FText& Text);
    void SetKills(const FText& Text);
    void SetDeaths(const FText& Text);
    void SetTeam(const FText& Text);
    void SetPlayerIndicatorVisibility(bool Visible);
    
protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* NameText;
    
    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillsText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* DeathsText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TeamText;

    UPROPERTY(meta = (BindWidget))
    UImage* PlayerImage;
    
};
