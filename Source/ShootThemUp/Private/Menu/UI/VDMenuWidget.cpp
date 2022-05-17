// Shoot Them Up Game. All Rights Reserved.


#include "Menu/UI/VDMenuWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "VDGameInstance.h"
#include "VDLevelItemWidget.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogVDMenuWidget, All, All);

void UVDMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &UVDMenuWidget::OnStartGame);
    }

    if(QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &UVDMenuWidget::OnQuitGame);
    }

    InitLevelItems();
}

void UVDMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    if(Animation != HideAnimation) return;
    
    const auto MyGameInstance = GetWorld()->GetGameInstance<UVDGameInstance>();
    if(!MyGameInstance) return;

    UGameplayStatics::OpenLevel(this, MyGameInstance->GetStartupLevel().LevelName);
}

void UVDMenuWidget::OnStartGame()
{
    PlayAnimation(HideAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
}

void UVDMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UVDMenuWidget::InitLevelItems()
{
    const auto MyGameInstance = GetWorld()->GetGameInstance<UVDGameInstance>();
    if(!MyGameInstance) return;

    checkf(MyGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

    if(!LevelItemsBox) return;
    LevelItemsBox->ClearChildren();

    for(auto LevelData: MyGameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<UVDLevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if(!LevelItemWidget) continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &UVDMenuWidget::OnLevelSelected);

        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }

    if(MyGameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(MyGameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(MyGameInstance->GetStartupLevel());
    }
}

void UVDMenuWidget::OnLevelSelected(const FLevelData& LevelData)
{
    const auto MyGameInstance = GetWorld()->GetGameInstance<UVDGameInstance>();
    if(!MyGameInstance) return;

    MyGameInstance->SetStartupLevel(LevelData);
    for(auto LevelItemWidget: LevelItemWidgets)
    {
        if(LevelItemWidget)
        {
            const auto IsSelected = LevelData.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

UVDGameInstance* UVDMenuWidget::GetVDGameInstance() const
{
    if(!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<UVDGameInstance>();
}
