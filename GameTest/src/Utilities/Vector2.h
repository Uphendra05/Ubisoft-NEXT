#pragma once
#ifndef _VECTOR2_H
#define _VECTOR2_H
#include <iostream>
#include <cmath>

namespace Engine
{

	class Vector2
	{
	public:

		//Constructors

		Vector2();
		Vector2( float x,  float y);
		Vector2(const Vector2& other);

		~Vector2() {};
		

		


		//Static Methods
		  float Dot(const Vector2& other) const ;

		static float Dot(const Vector2& lhs, const Vector2& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

		static Vector2 Reflect(Vector2& incident, Vector2& normal) {
			Vector2 norm = normal;
			float dotProduct = Vector2::Dot(incident, norm);
			return incident - norm * (2.0f * dotProduct);
		}

		static Vector2 Lerp(const Vector2& start, const Vector2& end, float t)
		{
			return start + (end - start) * t;
		}

		 float Cross(const Vector2& other) const ;
		

		//Static Properties
		Vector2& down();

		//Properties
		float magnitude() const;
		Vector2 normalized() const;
		
   
		


		//Operators
		Vector2& operator=(const Vector2& other);
		Vector2 operator+(const Vector2& other) const;
		Vector2& operator+=(const Vector2& other);
		Vector2 operator-(const Vector2& other) const;
		Vector2& operator-=(const Vector2& other);
		Vector2 operator*(float scalar) const;
		Vector2& operator*=(float scalar);
		Vector2 operator/(float scalar) const;
		Vector2& operator/=(float scalar);


		// Overload equality operators
		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;

		//Overload stream operator for printing
		friend std::ostream& operator<<(std::ostream& os, const Vector2& vec);


        float x, y;
		
	

	};

	


}
#endif