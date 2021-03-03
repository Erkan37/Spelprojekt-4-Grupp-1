/*
*	Author: Elia Rönning & Joel Schultz
*/

#pragma once
#include <math.h>
#include <cstdint>

namespace Utils
{
	template <class T>
	class Vector4
	{
	public:
		T x;
		T y;
		T z;
        T w;
		
		Vector4<T>()
			: x{0}, y{0}, z{0}, w{0}
		{}
		
		Vector4<T>(const T& aX, const T& aY, const T& aZ, const T& aW)
			: x{ aX }, y{ aY }, z{ aZ }, w{ aW }{};
		
		Vector4<T>(const Vector4<T>& aVector) = default;
		
		Vector4<T>& operator=(const Vector4<T>& aVector3) = default;
		
		~Vector4<T>() = default;
		
		T LengthSqr() const
		{
			return x * x + y * y + z * z + w * w;
		}
		
		T Length() const
		{
			return sqrt(x * x + y * y + z * z + w * w);
		}
		
		Vector4<T> GetNormalized() const
		{
			if (Length() == 0) return *this;

			const inverseLength = 1.0 / Length();
			return Vector4<T>(x * inverseLength, y * inverseLength, z * inverseLength, w * inverseLength);
		}
		
		void Normalize()
		{			
			*this = GetNormalized();
		}
		
		T Dot(const Vector4<T>& aVector) const
		{
			return this->x * aVector.x + this->y * aVector.y + this->z * aVector.z + this->w * aVector.w;
		}
	};
	
	template <class T>
	Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>&aVector1) 
	{
		return Vector4<T> (aVector0.x + aVector1.x,
                            aVector0.y + aVector1.y, 
                            aVector0.z + aVector1.z,
                            aVector0.w + aVector1.w);
	}
	
	template <class T>
	Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>&aVector1) 
	{
		return Vector4<T>(aVector0.x - aVector1.x,
			aVector0.y - aVector1.y,
			aVector0.z - aVector1.z,
            aVector0.w - aVector1.w);
	}
	
	template <class T>
	Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
	{
		return Vector4<T> (aVector.x * aScalar, aVector.y * aScalar, aVector.z * aScalar, aVector.w * aScalar);
	}
	
	template <class T>
	Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
	{
		return aVector * aScalar;
	}
	
	template <class T> 
	Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar)
	{
		const double inverseOfScalar = 1.0 / aScalar;
		return Vector4<T> (aVector.x * inverseOfScalar, aVector.y * inverseOfScalar, aVector.z * inverseOfScalar, aVector.w * inverseOfScalar);
	}
	template <class T> 
	void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
	{
		aVector0 = aVector0 + aVector1;
	}
	template <class T> 
	void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1) 
	{
		aVector0 = aVector0 - aVector1;
	}
	template <class T> 
	void operator*=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector = aVector * aScalar;
	}
	template <class T> 
	void operator/=(Vector4<T>& aVector, const T& aScalar)
	{
		aVector = aVector / aScalar;
	}
}

typedef Utils::Vector4<float> v4f;
typedef Utils::Vector4<double> v4d;
typedef Utils::Vector4<int32_t> v4i;
typedef Utils::Vector4<uint32_t> v4ui;