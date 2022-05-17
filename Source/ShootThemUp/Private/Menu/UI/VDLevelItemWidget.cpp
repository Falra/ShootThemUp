// Shoot Them Up Game. All Rights Reserved.


#include "Menu/UI/VDLevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UVDLevelItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(LevelSelectButton)
    {
        LevelSelectButton->OnClicked.AddDynamic(this, &UVDLevelItemWidget::OnLevelItemClicked);
        LevelSelectButton->OnHovered.AddDynamic(this, &UVDLevelItemWidget::OnLevelItemHovered);
        LevelSelectButton->OnUnhovered.AddDynamic(this, &UVDLevelItemWidget::OnLevelItemUnhovered);
    }
}

void UVDLevelItemWidget::OnLevelItemClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}

void UVDLevelItemWidget::OnLevelItemHovered()
{
    if(FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Visible);
    }
}

void UVDLevelItemWidget::OnLevelItemUnhovered()
{
    if(FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UVDLevelItemWidget::SetLevelData(const FLevelData& Data)
{
    LevelData = Data;

    if(LevelNameTextBlock)
    {
        LevelNameTextBlock->SetText(FText::FromName(LevelData.LevelDisplayName));
    }

    if(LevelImage)
    {
        LevelImage->SetBrushFromTexture(LevelData.LevelThumb);
    }
}

void UVDLevelItemWidget::SetSelected(bool IsSelected)
{
    if(LevelImage)
    {
        LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);
    }
}
