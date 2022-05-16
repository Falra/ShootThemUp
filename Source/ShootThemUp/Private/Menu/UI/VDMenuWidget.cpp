// Shoot Them Up Game. All Rights Reserved.


#include "Menu/UI/VDMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "VDGameInstance.h"

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
}

void UVDMenuWidget::OnStartGame()
{
    if(!GetWorld()) return;

    const auto MyGameInstance = GetWorld()->GetGameInstance<UVDGameInstance>();
    if(!MyGameInstance) return;

    if(MyGameInstance->GetStartupLevelName().IsNone())
    {
        UE_LOG(LogVDMenuWidget, Error, TEXT("Level name is NONE"));
        return;
    }
    UGameplayStatics::OpenLevel(this, MyGameInstance->GetStartupLevelName());
}

void UVDMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
