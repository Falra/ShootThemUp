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
    }
}

void UVDLevelItemWidget::OnLevelItemClicked()
{
    OnLevelSelected.Broadcast(LevelData);
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
    if(FrameImage)
    {
        FrameImage->SetVisibility(IsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}
