#include "stdafx.h"
#include "ComponentUtils.h"



namespace Engine
{
	FrameCounterComponent* ComponentUtils::mFrameCounter = new FrameCounterComponent();
	FrameCollisionComponent* ComponentUtils::pFrameCol = new FrameCollisionComponent();


	FrameCounterComponent* Engine::ComponentUtils::GetFrameCounter()
	{
		return mFrameCounter;
	}

	FrameCollisionComponent* ComponentUtils::GetFrameCollision()
	{
		return pFrameCol;
	}

}
