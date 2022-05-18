// Shoot Them Up Game. All Rights Reserved.


#include "Sound/VDSoundFunctionLibrary.h"
#include "Sound/SoundClass.h"

DEFINE_LOG_CATEGORY_STATIC(LogVDSoundFunctionLibrary, All, All);

void UVDSoundFunctionLibrary::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
    if(!SoundClass) return;
    SoundClass->Properties.Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
    UE_LOG(LogVDSoundFunctionLibrary, Display, TEXT("Sound class volume was changed: %s = %f"), *SoundClass->GetName(), Volume);
}

void UVDSoundFunctionLibrary::ToggleSoundClassVolume(USoundClass* SoundClass)
{
    if(!SoundClass) return;
    const auto NextVolume = SoundClass->Properties.Volume > 0 ? 0.0f : 1.0f;
    SetSoundClassVolume(SoundClass, NextVolume);
}
