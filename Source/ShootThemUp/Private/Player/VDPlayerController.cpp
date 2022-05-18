// Shoot Them Up Game. All Rights Reserved.


#include "Player/VDPlayerController.h"
#include "Components/VDRespawnComponent.h"
#include "VDGameModeBase.h"
#include "VDGameInstance.h"

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
    InputComponent->BindAction("Mute", IE_Pressed, this, &AVDPlayerController::OnMuteSound);
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

void AVDPlayerController::OnMuteSound()
{
    if(!GetWorld()) return;
    
    const auto MyGameInstance = GetWorld()->GetGameInstance<UVDGameInstance>();
    if(!MyGameInstance) return;;

    MyGameInstance->ToggleVolume();
}
