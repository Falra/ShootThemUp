// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VDCoreTypes.h"
#include "UI/VDBaseWidget.h"
#include "VDMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class UVDGameInstance;
class UVDLevelItemWidget;

UCLASS()
class SHOOTTHEMUP_API UVDMenuWidget : public UVDBaseWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelItemsBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

    virtual void NativeOnInitialized() override;

private:
    UPROPERTY()
    TArray<UVDLevelItemWidget*> LevelItemWidgets;

    UFUNCTION()
    void OnStartGame();

    UFUNCTION()
    void OnQuitGame();

    void InitLevelItems();
    void OnLevelSelected(const FLevelData& LevelData);
    UVDGameInstance* GetVDGameInstance() const;
};
