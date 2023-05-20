// Shoot Them Up. All Rights Reserved.


#include "Animations/STUWquipFinishedAnimNotify.h"

void USTUWquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}
