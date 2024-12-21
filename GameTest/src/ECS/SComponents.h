#pragma once
#include "ECSCore.h"
#include "../Utilities/Vector2.h"

#ifndef _SCOMPONENTS_H
#define _SCOMPONENTS_H

namespace Engine
{


	struct Transform
	{
		std::string componenetName = "Transform";

		Vector2 position = Vector2(0,0);
		float rotation = 0.0f;
		float scale = 1.0f;

		Vector2 worldPosition = Vector2(0,0);
		float worldrotation = 0.0f;
		float worldScale = 1.0f;

	};



}
#endif