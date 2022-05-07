// Shoot Them Up Game. All Rights Reserved.


#include "Animations/VDAnimNotify.h"

void UVDAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}