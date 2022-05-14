#pragma once
#include "Vector.hpp"

/* - Description:  A Plane object represents a plane with a direction (it has a normal that defines a side as outside, and one as inside) - */

namespace CommonUtilities
{
	template <typename T>
	class Plane
	{
	public:
		Plane();
		Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2);
		Plane(const Vector3<T>& aPoint0, const Vector3<T>& aNormal);

		void				InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2);
		void				InitWithPointAndNormal(const Vector3<T>& aPoint, const Vector3<T>& aNormal);
		bool				IsInside(const Vector3<T>& aPosition)		const;

		const Vector3<T>&	GetPoint()									const;
		const Vector3<T>&	GetNormal()									const;


	private:
		Vector3<T>			myPoint;
		Vector3<T>			myNormal;
	};

#pragma region DEFINITIONS

	template <typename T>
	Plane<T>::Plane()
		: myPoint{ 0.f, 0.f, 0.f }, myNormal{ 0.f, 0.f, 0.f }
	{
	}

	template <typename T>
	Plane<T>::Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
		: myPoint{ aPoint0 }, myNormal{ Vector3<T>(aPoint1 - aPoint0).Cross(aPoint2 - aPoint0) }
	{
	}

	template <typename T>
	Plane<T>::Plane(const Vector3<T>& aPoint0, const Vector3<T>& aNormal)
		: myPoint{ aPoint0 }, myNormal{ aNormal }
	{
		myNormal.Normalize();
	}

	template <typename T>
	void Plane<T>::InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
	{
		myPoint = aPoint0;

		myNormal = Vector3<T>(aPoint1 - aPoint0).Cross(aPoint2 - aPoint0);
		myNormal.Normalize();
	}

	template <typename T>
	void Plane<T>::InitWithPointAndNormal(const Vector3<T>& aPoint, const Vector3<T>& aNormal)
	{
		myPoint = aPoint;
		myNormal = aNormal;
		myNormal.Normalize();
	}

	template <typename T>
	bool Plane<T>::IsInside(const Vector3<T>& aPosition)	const
	{
		return myNormal.Dot(aPosition - myPoint) <= 0.0f;
	}

	template <typename T>
	const Vector3<T>& Plane<T>::GetPoint()					const
	{
		return myPoint;
	}

	template <typename T>
	const Vector3<T>& Plane<T>::GetNormal()					const
	{
		return myNormal;
	}

#pragma endregion DEFINITIONS
}
