#pragma once
#ifndef _VECTOR2TESTS_H
#define _VECTOR2TESTS_H

#include "Vector2.h"
#include "assert.h"
#include <iostream>

namespace Engine
{
	class Vector2Tests
	{
	public:
		static void RunAllTests();


		static void TestAdd(Vector2& v, Vector2& w);
		static void TestCompoundAdd(Vector2& v, Vector2& w);
		static void TestSubtract(Vector2& v, Vector2& w);
		static void TestCompoundSubtract(Vector2& v, Vector2& w);
		static void TestMultiply(Vector2& v, float& n);
		static void TestCompoundMultiply(Vector2& v, float& n);
		static void TestDivide(Vector2& v, float& n);
		static void TestCompoundDivide(Vector2& v, float& n);
		static void TestEquals(Vector2& v, Vector2& w);
		static void TestNotEquals(Vector2& v, Vector2& w);
		static void TestDot(Vector2& v, Vector2& w);
		static void TestCross(Vector2& v, Vector2& w);
		static void TestMagnitude(Vector2& v);
		static void TestNormalized(Vector2& v);
		
		



		

	};
}

#endif

