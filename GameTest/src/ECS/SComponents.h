#pragma once
#include "ECSCore.h"
#include "../Utilities/Vector2.h"

namespace Engine
{


	struct Transform
	{

		Vector2 position = Vector2(0,0);
		float rotation = 0.0f;
		float scale = 1.0f;

		Vector2 worldPosition = Vector2(0,0);
		float worldrotation = 0.0f;
		float worldScale = 1.0f;

	};



}