// Shoot Them Up Game. All Rights Reserved.


#include "UI/VDGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void AVDGameHUD::DrawHUD()
{
    Super::DrawHUD();

    //DrawCrossHair();
}

void AVDGameHUD::BeginPlay()
{
    Super::BeginPlay();
    auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
    if(PlayerHUDWidget)
    {
        PlayerHUDWidget->AddToViewport();
    }
}

void AVDGameHUD::DrawCrossHair()
{
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
    constexpr float HalfLineSize = 10.0f;
    constexpr float LineThickness = 2.0f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}
