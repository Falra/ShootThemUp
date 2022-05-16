// Shoot Them Up Game. All Rights Reserved.


#include "Menu/UI/VDMenuHUD.h"
#include "Blueprint/UserWidget.h"

void AVDMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if(MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
        if(MenuWidget)
        {
            MenuWidget->AddToViewport();
        }
    }
}
