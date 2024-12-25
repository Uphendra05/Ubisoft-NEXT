#pragma once
#ifndef _SCOMPONENTS_H
#define _SCOMPONENTS_H

#include "ECSCore.h"
#include "../Utilities/Vector2.h"



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

	struct SpriteRenderer
	{
		 std::string fileName;
		 int rows = 0;
		 int cols = 0;
	};



}
#endif