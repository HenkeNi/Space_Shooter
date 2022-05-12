#pragma once
#include <cassert>
#include <cmath>

namespace CommonUtilities
{
	template <class T>
	class Vector2
	{
	public:
		Vector2();
		Vector2(const T& aX, const T& aY);
		Vector2(const Vector2& aVector)				= default;
		~Vector2()									= default;

		Vector2&	operator=(const Vector2&)		= default;
		Vector2		operator-()							const;

		/* -	Methods		- */
		T			LengthSqr()						const;
		T			Length()						const;
		T			Dot(const Vector2& another)		const;
		Vector2		GetNormalized()					const;
		void		Normalize();

		/* -	Members		- */
		T x;
		T y;
	};

#pragma region DEFINITIONS

	template <class T>
	Vector2<T>::Vector2()
		: x{ 0 }, y{ 0 }
	{
	}

	template <class T>
	Vector2<T>::Vector2(const T& aX, const T& aY)
		: x{ aX }, y{ aY }
	{
	}

	template <class T>
	T Vector2<T>::LengthSqr() const
	{
		return (x * x) + (y * y);
	}

	template <class T>
	T Vector2<T>::Length() const
	{
		return std::sqrt((x * x) + (y * y));
	}

	template <class T>
	T Vector2<T>::Dot(const Vector2<T>& another) const
	{
		return (x * another.x) + (y * another.y);
	}

	template <class T>
	Vector2<T> Vector2<T>::GetNormalized() const
	{
		auto length = 1 / Length();
		assert(length != 0.0);

		return { x * length, y * length };
	}

	template <class T>
	void Vector2<T>::Normalize()
	{
		auto length = 1 / Length();
		assert(length != 0.0f);

		x *= length;
		y *= length;
	}


	/* -		Overloaded Operators		 - */
	template <class T>
	Vector2<T> Vector2<T>::operator-()	const
	{
		return { -x, -y };
	}

	template <class T>
	Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return { aVector0.x + aVector1.x, aVector0.y + aVector1.y };
	}

	template <class T>
	Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return { aVector0.x - aVector1.x, aVector0.y - aVector1.y };
	}

	template <class T>
	Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
	{
		return { aVector.x * aScalar, aVector.y * aScalar };
	}

	template <class T>
	Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
	{
		return aVector * aScalar;
	}

	template <class T>
	Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
	{
		assert(aScalar != 0);
		return Vector2<T>(aVector.x * (1 / aScalar), aVector.y * (1 / aScalar));
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
		assert(aScalar != 0);
		aVector = aVector / aScalar;
	}

	template <class T>
	bool operator==(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return (aVector0.x == aVector1.x && aVector0.y == aVector1.y);
	}

	template <class T>
	bool operator!=(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
	{
		return !(aVector0 == aVector1);
	}

#pragma endregion DEFINITIONS
} 