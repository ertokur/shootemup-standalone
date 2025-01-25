// Erbol Tokur

#pragma once

#include "CoreMinimal.h"

class SHOOTEMUP_API SEUAnimUtils
{
public:
	template <typename T>
	static TObjectPtr<T> FindNotifyByClass(TObjectPtr<UAnimSequenceBase> Animation)
	{
		if (IsValid(Animation))
		{
			for (const auto NotifyEvent : Animation->Notifies)
			{
				auto AnimNotify = Cast<T>(NotifyEvent.Notify);
				if (AnimNotify)
				{
					return AnimNotify;
				}
			}
		}
	
		return nullptr;
	}
};