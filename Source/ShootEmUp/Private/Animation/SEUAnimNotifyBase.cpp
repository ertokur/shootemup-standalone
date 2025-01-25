// Erbol Tokur


#include "Animation/SEUAnimNotifyBase.h"


void USEUAnimNotifyBase::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	OnNotifyFinished.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation, EventReference);
}