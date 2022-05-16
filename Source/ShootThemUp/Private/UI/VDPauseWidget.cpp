// Shoot Them Up Game. All Rights Reserved.


#include "UI/VDPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

void UVDPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if(ResumeGameButton)
    {
        ResumeGameButton->OnClicked.AddDynamic(this, &UVDPauseWidget::OnResumeGame);
    }
}

void UVDPauseWidget::OnResumeGame()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
