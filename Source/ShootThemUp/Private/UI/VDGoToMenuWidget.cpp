// Shoot Them Up Game. All Rights Reserved.


#include "UI/VDGoToMenuWidget.h"

#include "VDGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogVDGoToMenuWidget, All, All);

void UVDGoToMenuWidget::NativeOnInitialized()
{
    if(GoToMenuButton)
    {
        GoToMenuButton->OnClicked.AddDynamic(this, &UVDGoToMenuWidget::OnGoToMenu);
    }

    Super::NativeOnInitialized();
}

void UVDGoToMenuWidget::OnGoToMenu()
{
    if(!GetWorld()) return;

    const auto MyGameInstance = GetWorld()->GetGameInstance<UVDGameInstance>();
    if(!MyGameInstance) return;

    if(MyGameInstance->GetMenuLevelName().IsNone())
    {
        UE_LOG(LogVDGoToMenuWidget, Error, TEXT("Menu name is NONE"));
        return;
    }
    UGameplayStatics::OpenLevel(this, MyGameInstance->GetMenuLevelName());
}
