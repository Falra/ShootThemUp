// Shoot Them Up Game. All Rights Reserved.


#include "UI/VDPlayerHUDWidget.h"
#include "Components/VDHealthComponent.h"
#include "Components/VDWeaponComponent.h"
#include "VDUtils.h"
#include "Components/ProgressBar.h"

float UVDPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComp = VDUtils::GetVDPlayerComponent<UVDHealthComponent>(GetOwningPlayerPawn());
    if(!HealthComp) return 0.0f;
    
    return HealthComp->GetHealthPercent();
}

bool UVDPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComp = VDUtils::GetVDPlayerComponent<UVDWeaponComponent>(GetOwningPlayerPawn());
    if(!WeaponComp) return false;

    return WeaponComp->GetCurrentWeaponUIData(UIData);
}

bool UVDPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto WeaponComp = VDUtils::GetVDPlayerComponent<UVDWeaponComponent>(GetOwningPlayerPawn());
    if(!WeaponComp) return false;

    return WeaponComp->GetCurrentWeaponAmmoData(AmmoData);
}

bool UVDPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComp = VDUtils::GetVDPlayerComponent<UVDHealthComponent>(GetOwningPlayerPawn());;
    return HealthComp && !HealthComp->IsDead();
    
}

bool UVDPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

void UVDPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    if(GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UVDPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
}

void UVDPlayerHUDWidget::OnHealthChanged(float NewHealth, float DeltaHealth)
{
    if (DeltaHealth < 0.0f)
    {
        OnTakeDamage();

        if(!IsAnimationPlaying(DamageAnimation))
        {
            PlayAnimation(DamageAnimation);
        }
    }
    
    UpdateHealthBar();
}

void UVDPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
    const auto HealthComp = VDUtils::GetVDPlayerComponent<UVDHealthComponent>(NewPawn);
    if(HealthComp)
    {
        HealthComp->OnHealthChanged.AddUObject(this, &UVDPlayerHUDWidget::OnHealthChanged);
    }
    UpdateHealthBar();
}

int32 UVDPlayerHUDWidget::GetKillsNum() const
{
    const auto PlayerState = GetPlayerState();
    if(!PlayerState) return 0;

    return PlayerState->GetKillsNum();
}

int32 UVDPlayerHUDWidget::GetDeathsNum() const
{
    const auto PlayerState = GetPlayerState();
    if(!PlayerState) return 0;

    return PlayerState->GetDeathsNum();
}

FString UVDPlayerHUDWidget::FormatBullets(int32 BulletsNum) const
{
    constexpr int32 MaxLen = 3;

    auto BulletStr = FString::FromInt(BulletsNum);
    const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();

    if (SymbolsNumToAdd > 0)
    {
        constexpr TCHAR PrefixSymbol = '0';
        BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
    }

    return BulletStr;
}

void UVDPlayerHUDWidget::UpdateHealthBar()
{
    if(HealthProgressBar)
    {
        HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
    }
}

AVDPlayerState* UVDPlayerHUDWidget::GetPlayerState() const
{
    return GetOwningPlayer() ? GetOwningPlayer()->GetPlayerState<AVDPlayerState>() : nullptr;
}