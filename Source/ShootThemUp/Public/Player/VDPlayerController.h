// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VDCoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "VDPlayerController.generated.h"

class UVDRespawnComponent;

UCLASS()
class SHOOTTHEMUP_API AVDPlayerController : public APlayerController
{
    GENERATED_BODY()
public:
    AVDPlayerController();
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UVDRespawnComponent* RespawnComponent;

    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    void OnPauseGame();
    void OnMatchStateChanged(EVDMatchState State);
    void OnMuteSound();
};
