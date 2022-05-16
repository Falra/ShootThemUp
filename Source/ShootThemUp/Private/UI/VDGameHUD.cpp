// Shoot Them Up Game. All Rights Reserved.


#include "UI/VDGameHUD.h"
#include "Engine/Canvas.h"
#include "VDGameModeBase.h"
#include "Blueprint/UserWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogVDGameHUD, All, All);

void AVDGameHUD::DrawHUD()
{
    Super::DrawHUD();

    //DrawCrossHair();
}

void AVDGameHUD::BeginPlay()
{
    Super::BeginPlay();
    
    GameWidgets.Add(EVDMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(EVDMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(EVDMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));
    
    for(const auto GameWidgetPair: GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if(!GameWidget) continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    
    if(GetWorld())
    {
        const auto GameMode = Cast<AVDGameModeBase>(GetWorld()->GetAuthGameMode());
        if(GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &AVDGameHUD::OnMatchStateChanged);
        }
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

void AVDGameHUD::OnMatchStateChanged(EVDMatchState MatchState)
{
    if(CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if(GameWidgets.Contains(MatchState))
    {
        CurrentWidget = GameWidgets[MatchState];
    }

    if(CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }
    
    UE_LOG(LogVDGameHUD, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(MatchState));
}
