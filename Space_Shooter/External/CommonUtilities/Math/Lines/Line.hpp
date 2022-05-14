#pragma once
#include "Vector.hpp"

/* - Description: a Line object is represented by a directed infinite line - */

namespace CommonUtilities
{
	template <typename T>
	class Line
	{
	public:
		Line();
		Line(const Line& aLine);
		Line(const Vector2<T>& aPoint, const Vector2<T>& aDirection);

		void				InitWith2Points(const Vector2<T>& aPoint1, const Vector2<T>& aPoint2);
		void				InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>& aDirection);

		const Vector2<T>	GetPoint()		const;
		const Vector2<T>	GetDirection()	const;
	
	private:
		Vector2<T>			myPoint;
		Vector2<T>			myDirection;
	};

#pragma region DEFINITIONS

	template <typename T>
	Line<T>::Line()
		: myPoint{ 0, 0 }, myDirection{ 0, 0 }
	{
	}

	template <typename T>
	Line<T>::Line(const Line& aLine)
		: myPoint{ aLine.myPoint }, myDirection{ aLine.myDirection }
	{
	}

	template <typename T>
	Line<T>::Line(const Vector2<T>& aPoint, const Vector2<T>& aDirection)
		: myPoint{ aPoint }, myDirection{ aDirection }
	{
	}

	template <typename T>
	void Line<T>::InitWith2Points(const Vector2<T>& aPoint1, const Vector2<T>& aPoint2)
	{
		myPoint = aPoint1;
		myDirection = aPoint2 - aPoint1;
	}

	template <typename T>
	void Line<T>::InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>& aDirection)
	{
		myPoint		= aPoint;
		myDirection = aDirection;
	}

	template <typename T>
	const Vector2<T> Line<T>::GetPoint()		const
	{
		return myPoint;
	}

	template <typename T>
	const Vector2<T> Line<T>::GetDirection()	const
	{
		return myDirection;
	}

#pragma endregion DEFINITIONS
}