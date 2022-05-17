// Shoot Them Up Game. All Rights Reserved.


#include "Menu/UI/VDMenuHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/VDBaseWidget.h"

void AVDMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if(MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<UVDBaseWidget>(GetWorld(), MenuWidgetClass);
        if(MenuWidget)
        {
            MenuWidget->AddToViewport();
            MenuWidget->Show();
        }
    }
}
