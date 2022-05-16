// Shoot Them Up Game. All Rights Reserved.


#include "UI/VDPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

bool UVDPauseWidget::Initialize()
{
    const auto InitStatus = Super::Initialize();

    if(ResumeGameButton)
    {
        ResumeGameButton->OnClicked.AddDynamic(this, &UVDPauseWidget::OnResumeGame);
    }
    
    return InitStatus;
}

void UVDPauseWidget::OnResumeGame()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
