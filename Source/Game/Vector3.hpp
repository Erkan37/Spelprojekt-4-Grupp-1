/*
*	Author: Elia Rönning & Joel Schultz
*/

#pragma once
#include <math.h>

namespace Utils
{
	template <class T>
	class Vector3
	{
	public:
		T x;
		T y;
		T z;
		
		Vector3<T>()
			: x{0}, y{0}, z{0}
		{}
		
		Vector3<T>(const T& aX, const T& aY, const T& aZ)
			: x{ aX }, y{ aY }, z{ aZ }{};
		
		Vector3<T>(const Vector3<T>& aVector) = default;
		
		Vector3<T>& operator=(const Vector3<T>& aVector3) = default;
		
		~Vector3<T>() = default;
		
		T LengthSqr() const
		{
			return x * x + y * y + z * z;
		}
		
		T Length() const
		{
			return sqrt(x * x + y * y + z * z);
		}
		
		Vector3<T> GetNormalized() const
		{
			if (Length() == 0) return *this;

			const double inverseLength = 1.0 / Length();
			return Vector3<T>(x * inverseLength, y * inverseLength, z * inverseLength);
		}
		
		void Normalize()
		{		
			*this = GetNormalized();
		}
		
		T Dot(const Vector3<T>& aVector) const
		{
			return this->x * aVector.x + this->y * aVector.y + this->z * aVector.z;
		}
		
		Vector3<T> Cross(const Vector3<T>& aVector) const
		{
			return Vector3<T> 
			(
				(this->y * aVector.z) - (aVector.y * this->z), 
				(this->z * aVector.x - aVector.z * this->x), 
				(this->x * aVector.y - aVector.x * this->y)
			);
		}
	};
	
	template <class T>
	Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>&aVector1) 
	{
		return Vector3<T> (aVector0.x + aVector1.x,
							 aVector0.y + aVector1.y, 
							 aVector0.z + aVector1.z);
	}
	
	template <class T>
	Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>&aVector1) 
	{
		return Vector3<T>(aVector0.x - aVector1.x,
			aVector0.y - aVector1.y,
			aVector0.z - aVector1.z);
	}
	
	template <class T>
	Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
	{
		return Vector3<T> (aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar);
	}
	
	template <class T>
	Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
	{
		return aVector * aScalar;
	}
	
	template <class T> 
	Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
	{
		const double inverseOfScalar = 1.0 / aScalar;
		return Vector3<T> (aVector.x * inverseOfScalar, aVector.y * inverseOfScalar, aVector.z * inverseOfScalar);
	}
	
	template <class T> 
	void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
	{
		aVector0 = aVector0 + aVector1;
	}
	
	template <class T> 
	void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1) 
	{
		aVector0 = aVector0 - aVector1;
	}
	
	template <class T> 
	void operator*=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector = aVector * aScalar;
	}
	
	template <class T> 
	void operator/=(Vector3<T>& aVector, const T& aScalar)
	{
		aVector = aVector / aScalar;
	}
}

typedef Utils::Vector3<float> v3f;
typedef Utils::Vector3<double> v3d;
typedef Utils::Vector3<int32_t> v3i;
typedef Utils::Vector3<uint32_t> v3ui;