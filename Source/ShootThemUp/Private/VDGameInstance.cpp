// Shoot Them Up Game. All Rights Reserved.


#include "VDGameInstance.h"
#include "Sound/VDSoundFunctionLibrary.h"

void UVDGameInstance::ToggleVolume()
{
    UVDSoundFunctionLibrary::ToggleSoundClassVolume(MasterSoundClass);
}
