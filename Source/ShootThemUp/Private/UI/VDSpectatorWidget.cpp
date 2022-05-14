// Shoot Them Up Game. All Rights Reserved.


#include "UI/VDSpectatorWidget.h"
#include "VDUtils.h"
#include "Components/VDRespawnComponent.h"

bool UVDSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
    const auto RespawnComponent = VDUtils::GetVDPlayerComponent<UVDRespawnComponent>(GetOwningPlayer());
    if(!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

    CountDownTime = RespawnComponent->GetRespawnCountDown();
    return true;
}
