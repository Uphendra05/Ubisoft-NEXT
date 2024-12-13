#pragma once
#include "ECSCore.h"
#include "../Utilities/Vector2.h"

namespace Engine
{


	struct Transform
	{

		Vector2 position;
		float rotation;
		float scale;

		Vector2 worldPosition;
		float worldrotation;
		float worldScale;

	};



}