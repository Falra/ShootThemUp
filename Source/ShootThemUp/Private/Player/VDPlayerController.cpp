// Shoot Them Up Game. All Rights Reserved.


#include "Player/VDPlayerController.h"
#include "VDGameModeBase.h"
#include "Components/VDRespawnComponent.h"

AVDPlayerController::AVDPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<UVDRespawnComponent>("RespawnComponent");
}

void AVDPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if(GetWorld())
    {
        const auto GameMode = Cast<AVDGameModeBase>(GetWorld()->GetAuthGameMode());
        if(GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &AVDPlayerController::OnMatchStateChanged);
        }
    }
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

void AVDPlayerController::OnMatchStateChanged(EVDMatchState State)
{
    if(State == EVDMatchState::InProgress)
    {
        SetInputMode(FInputModeGameOnly()); 
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly()); 
        bShowMouseCursor = true;
    }
}
