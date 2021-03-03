/*
*	Author: Elia Rönning & Joel Schultz
*/

#pragma once
#include <math.h> 

namespace Tga2D
{
	template <class T>
	class Vector2;
}

namespace Utils
{
	template <class T>
	class Vector2
	{
	public:
		T x;
		T y;

		Vector2<T>()
			: x{0}, y{0}
		{}
		Vector2<T>(const T& aX, const T& aY)
			: x{ aX }, y{ aY }{};
		Vector2<T>(const Tga2D::Vector2<T>& aVec)
			: x{ aVec.x }, y{ aVec.y }
		{}

		Vector2<T>(const Vector2<T>& aVector) = default;
		Vector2<T>& operator=(const Vector2<T>& aVector3) = default;
		~Vector2<T>() = default;

		T LengthSqr() const
		{
			return x * x + y * y;
		}

		T Length() const
		{
			return sqrt(x * x + y * y);
		}

		Vector2<T> GetNormalized() const
		{
			if (Length() == 0) return *this;

			const double inverseLength = 1.0 / Length();
			return Vector2<T>(x * inverseLength, y * inverseLength);
		}
		void Normalize()
		{			
			*this = GetNormalized();
		}

		T Dot(const Vector2<T>& aVector) const
		{
			return this->x * aVector.x + this->y * aVector.y;
		}

		operator Tga2D::Vector2<T> const () const
		{
			return { x, y };
		}
	};

	template <class T>
	Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>&aVector1) 
	{
		return Vector2<T> (aVector0.x + aVector1.x,
							 aVector0.y + aVector1.y);
	}

	template <class T>
	Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>&aVector1) 
	{
		return Vector2<T>(aVector0.x - aVector1.x,
			aVector0.y - aVector1.y);
	}

	template <class T>
	Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
	{
		return Vector2<T> (aVector.x * aScalar, aVector.y * aScalar);
	}

	template <class T>
	Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{
		return aVector * aScalar;
	}

	template <class T> 
	Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
	{
		const double inverseOfScalar = 1.0 / aScalar;
		return Vector2<T> (aVector.x * inverseOfScalar, aVector.y * inverseOfScalar);
	}

	template <class T> 
	void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		aVector0 = aVector0 + aVector1;
	}

	template <class T> 
	void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1) 
	{
		aVector0 = aVector0 - aVector1;
	}

	template <class T> 
	void operator*=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector = aVector * aScalar;
	}

	template <class T> 
	void operator/=(Vector2<T>& aVector, const T& aScalar)
	{
		aVector = aVector / aScalar;
	}
}

typedef Utils::Vector2<float> v2f;
typedef Utils::Vector2<double> v2d;
typedef Utils::Vector2<int32_t> v2i;
typedef Utils::Vector2<uint32_t> v2ui;