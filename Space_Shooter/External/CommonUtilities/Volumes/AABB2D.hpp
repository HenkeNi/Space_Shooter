#pragma once
#include "Vector.hpp"

/* - Axis-Aligned Bounding Box (2D) - */

namespace CommonUtilities
{
	template <typename T>
	class AABB2D
	{
	public:
		AABB2D();
		AABB2D(const AABB2D& aAABB2D);
		AABB2D(const Vector2<T>& aMin, const Vector2<T>& aMax);

		void				InitWithMinAndMax(const Vector2<T>& aMin, const Vector2<T>& aMax);
		bool				IsInside(const Vector2<T>& aPosition)	const;

		const Vector2<T>&	GetMinPoint()							const;
		const Vector2<T>&	GetMaxPoint()							const;
		Vector2<T>			GetCenter()								const;
		T					GetWidth()								const;
		T					GetHeight()								const;

	private:
		Vector2<T>			myMinPoint;
		Vector2<T>			myMaxPoint;
	};

#pragma region DEFINITIONS

	template <class T>
	AABB2D<T>::AABB2D()
		: myMinPoint{ 0, 0 }, myMaxPoint{ 0, 0 }
	{
	}

	template <class T>
	AABB2D<T>::AABB2D(const AABB2D& aAABB2D)
		: myMinPoint{ aAABB2D.myMinPoint }, myMaxPoint{ aAABB2D.myMaxPoint }
	{
	}

	template <class T>
	AABB2D<T>::AABB2D(const Vector2<T>& aMin, const Vector2<T>& aMax)
		: myMinPoint{ aMin }, myMaxPoint{ aMax }
	{
	}

	template <class T>
	void AABB2D<T>::InitWithMinAndMax(const Vector2<T>& aMin, const Vector2<T>& aMax)
	{
		myMinPoint = aMin;
		myMaxPoint = aMax;
	}

	template <class T>
	bool AABB2D<T>::IsInside(const Vector2<T>& aPosition)	const
	{
		if (myMinPoint.x > aPosition.x) { return false; }
		if (myMinPoint.y > aPosition.y) { return false; }

		if (myMaxPoint.x < aPosition.x) { return false; }
		if (myMaxPoint.y < aPosition.y) { return false; }

		return true;
	}

	template <class T>
	const Vector2<T>& AABB2D<T>::GetMinPoint()	const
	{
		return myMinPoint;
	}

	template <class T>
	const Vector2<T>& AABB2D<T>::GetMaxPoint()	const
	{
		return myMaxPoint;
	}

	template <class T>
	Vector2<T> AABB2D<T>::GetCenter()			const
	{
		return { myMaxPoint.x - (GetWidth() * 0.5f), myMaxPoint.y - (GetHeight() * 0.5f) };
	}

	template <class T>
	T AABB2D<T>::GetWidth()						const
	{
		return myMaxPoint.x - myMinPoint.x;
	}

	template <class T>
	T AABB2D<T>::GetHeight()					const
	{
		return myMaxPoint.y - myMinPoint.y;
	}

#pragma endregion DEFINITIONS
}