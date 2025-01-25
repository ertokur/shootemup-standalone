// Erbol Tokur

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SEUAnimNotifyBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FNotifyFinishedSignature, TObjectPtr<USkeletalMeshComponent>);

/**
 * 
 */
UCLASS()
class SHOOTEMUP_API USEUAnimNotifyBase : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	FNotifyFinishedSignature OnNotifyFinished;
};