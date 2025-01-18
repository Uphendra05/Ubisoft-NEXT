#include "stdafx.h"
#include "Vector2.h"


namespace Engine
{

	Engine::Vector2::Vector2()
	{
		this->x = 0;
		this->y = 0;
	}

	Engine::Vector2::Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Engine::Vector2::Vector2(const Vector2& other)
	{
		this->x = other.x;
		this->y = other.y;
	}



	 float Engine::Vector2::Dot(const Vector2& other) const
	{
		return x * other.x + y * other.y;
	}

	
	 float Engine::Vector2::Cross(const Vector2& other) const
	{
		return x * other.y - y * other.x;
	}

	
	Vector2& Engine::Vector2::down()
	{
		static Vector2 downVector(0, -1);

		return downVector;
	}

	float Engine::Vector2::magnitude() const
	{
		return std::sqrt(x * x + y * y);
	}

	Vector2 Engine::Vector2::normalized() const
	{
		float length = magnitude();
		if (length != 0.0f) 
		{
			return (*this) / length;
		}
		else 
		{
			std::cerr << "Error: Normalizing the zero vector!" << std::endl;
			return Vector2();
		}
	}


	Vector2& Engine::Vector2::operator=(const Vector2& other)
	{
		if (this != &other)
		{
			x = other.x;
			y = other.y;
		}
		return *this;
	}

	Vector2 Engine::Vector2::operator+(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2& Engine::Vector2::operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2 Engine::Vector2::operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	Vector2& Engine::Vector2::operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2 Engine::Vector2::operator*(float scalar) const
	{
		return Vector2(x * scalar, y * scalar);
	}

	Vector2& Engine::Vector2::operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2 Engine::Vector2::operator/(float scalar) const
	{
		return Vector2(x / scalar, y / scalar);
	}

	Vector2& Engine::Vector2::operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	bool Engine::Vector2::operator==(const Vector2& other) const
	{
		return x == other.x && y == other.y;
	}

	bool Engine::Vector2::operator!=(const Vector2& other) const
	{
		return !(*this == other);
	}

	std::ostream& Engine::operator<<(std::ostream& os, const Vector2& vec)
	{
		os << "(" << vec.x << ", " << vec.y << ")";
		return os;
	}


}
