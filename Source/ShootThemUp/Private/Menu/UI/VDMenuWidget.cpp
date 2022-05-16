// Shoot Them Up Game. All Rights Reserved.


#include "Menu/UI/VDMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UVDMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &UVDMenuWidget::OnStartGame);
    }
}

void UVDMenuWidget::OnStartGame()
{
    const FName StartupLevelName = "TestLevel";
    UGameplayStatics::OpenLevel(this, StartupLevelName);
}
