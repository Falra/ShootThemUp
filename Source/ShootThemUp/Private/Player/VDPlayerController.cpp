// Shoot Them Up Game. All Rights Reserved.


#include "Player/VDPlayerController.h"
#include "Components/VDRespawnComponent.h"
#include "GameFramework/GameModeBase.h"

AVDPlayerController::AVDPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<UVDRespawnComponent>("RespawnComponent");
}

void AVDPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if(!InputComponent) return;

    InputComponent->BindAction("PauseGame", IE_Pressed, this, &AVDPlayerController::OnPauseGame);
}

void AVDPlayerController::OnPauseGame()
{
    if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->SetPause(this);
}
