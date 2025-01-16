#pragma once
#ifndef _COMPONENTUTILS_H
#define _COMPONENTUTILS_H
#include "src/ECS/SComponents.h"

namespace Engine
{
	class ComponentUtils
	{
	public:

		static FrameCounterComponent* GetFrameCounter();
		static FrameCollisionComponent* GetFrameCollision();


	private:
		static FrameCounterComponent* mFrameCounter;
		static FrameCollisionComponent* pFrameCol;


	};

}
#endif
