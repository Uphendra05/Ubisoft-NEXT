#include "stdafx.h"
#include "Vector2Tests.h"


namespace Engine
{

void Engine::Vector2Tests::RunAllTests()
{
	Vector2 v = Vector2(1.5f, 3.5f);
	Vector2 w = Vector2(1.5f, 3.5f);
	Vector2 d = Vector2(0, -1);
	float n = 2.0f;

	TestAdd(v, w);
	TestCompoundAdd(v, w);
	TestSubtract(v, w);
	TestCompoundSubtract(v, w);
	TestMultiply(v, n);
	TestCompoundMultiply(v, n);
	TestDivide(v, n);
	TestCompoundDivide(v, n);	
	TestEquals( v,  w);
	TestNotEquals(v,  w);
	TestDot(v, w);
	TestCross(v, w);
	
	TestMagnitude(v);
	TestNormalized( v);

}

void Engine::Vector2Tests::TestAdd(Vector2& v, Vector2& w)
{
	Vector2 u = v + w;
	assert(u == Vector2(3.0f, 7.0f));
}

void Engine::Vector2Tests::TestCompoundAdd(Vector2& v, Vector2& w)
{
	Vector2 u = v + w;
	u += u;
	assert(u == Vector2(6.0f, 14.0f));
}

void Engine::Vector2Tests::TestSubtract(Vector2& v, Vector2& w)
{
	Vector2 u = v - w;
	assert(u == Vector2(-3.0f, -7.0f));

}

void Engine::Vector2Tests::TestCompoundSubtract(Vector2& v, Vector2& w)
{
	Vector2 u = v - w;
	u -= u;
	assert(u == Vector2(0.0f, 0.0f));
}

void Engine::Vector2Tests::TestMultiply(Vector2& v, float& n)
{
	Vector2 u = v * n;
	assert(u == Vector2(9.0f, 21.0f));
}

void Engine::Vector2Tests::TestCompoundMultiply(Vector2& v, float& n)
{
	Vector2 u = v * n;
	u *= n;
	assert(u == Vector2(81.0f, 441.0f));
}

void Engine::Vector2Tests::TestDivide(Vector2& v, float& n)
{
	Vector2 u = v / n;

	assert(u == Vector2(0.5f, 1.0f));
}

void Engine::Vector2Tests::TestCompoundDivide(Vector2& v, float& n)
{
	Vector2 u = v / n;
	u /= n;
	assert(u == Vector2(0.5f, 1.0f));
}

void Engine::Vector2Tests::TestEquals(Vector2& v, Vector2& w)
{
	assert(v == w);
}

void Engine::Vector2Tests::TestNotEquals(Vector2& v, Vector2& w)
{
	assert(v != w);
}

void Engine::Vector2Tests::TestDot(Vector2& v, Vector2& w)
{
	float dot = v.Dot(w);

	assert(dot == 32.0f);
}

void Engine::Vector2Tests::TestCross(Vector2& v, Vector2& w)
{
	float cross = v.Cross(w);

	assert(cross == 32.0f);

}



void Engine::Vector2Tests::TestMagnitude(Vector2& v)
{
	float length = v.magnitude();

	assert(length == sqrtf(14));
}

void Engine::Vector2Tests::TestNormalized(Vector2& v)
{
	float length = v.magnitude();
	Vector2 u = v.normalized();

	assert(u == Vector2(v.x / length, v.y / length));
}

}
