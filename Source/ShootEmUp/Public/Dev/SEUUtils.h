#pragma once

class SEUUtils
{
public:
	
	template <typename T>
	static T* GetPlayerComponent(class AActor* OtherActor)
	{
		if (OtherActor)
		{
			if (const auto Component = OtherActor->GetComponentByClass(T::StaticClass()))
			{
				return Cast<T>(Component);
			}
		}

		return nullptr;
	}
};