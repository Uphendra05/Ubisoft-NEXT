#pragma once
#ifndef _MATHUTILS_H
#define _MATHUTILS_H

namespace Engine
{

	 class MathUtils
	{

	public:
		template <typename T>

		static T Max(T a, T b)
		{
			return (a > b) ? a : b;
		}
		template <typename T>

		static T Min(T a, T b)
		{
			return (a < b) ? a : b;
		}

		template <typename T>
		static  T Clamp(T value, T min, T max)
		{
			if (value < min) return min;
			if (value > max) return max;
			return value;
		}


	};




}
#endif