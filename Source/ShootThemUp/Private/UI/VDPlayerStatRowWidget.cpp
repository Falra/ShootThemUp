// Shoot Them Up Game. All Rights Reserved.


#include "UI/VDPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UVDPlayerStatRowWidget::SetPlayerName(const FText& Text)
{
    if(!NameText) return;
    NameText->SetText(Text);
}

void UVDPlayerStatRowWidget::SetKills(const FText& Text)
{
    if(!KillsText) return;
    KillsText->SetText(Text);
}

void UVDPlayerStatRowWidget::SetDeaths(const FText& Text)
{
    if(!DeathsText) return;
    DeathsText->SetText(Text);
}

void UVDPlayerStatRowWidget::SetTeam(const FText& Text)
{
    if(!TeamText) return;
    TeamText->SetText(Text);
}

void UVDPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
    if(!PlayerImage) return;
    PlayerImage->SetVisibility( Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UVDPlayerStatRowWidget::SetTeamColor(const FLinearColor& Color)
{
    if(!TeamImage) return;
    TeamImage->SetColorAndOpacity(Color);
}
