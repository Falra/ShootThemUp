// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VDBaseWidget.generated.h"

UCLASS()
class SHOOTTHEMUP_API UVDBaseWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void Show();
    
protected:
    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ShowAnimation;
};
