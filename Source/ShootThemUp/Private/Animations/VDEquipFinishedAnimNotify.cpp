// Shoot Them Up Game. All Rights Reserved.


#include "Animations/VDEquipFinishedAnimNotify.h"

void UVDEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}
