#pragma once
#include "Vector.hpp"

/* - Axis-Aligned Bounding Box (3D) - */

namespace CommonUtilities
{
	template <typename T>
	class AABB3D
	{
	public:
		AABB3D();
		AABB3D(const AABB3D& aAABB3D);
		AABB3D(const Vector3<T>& aMin, const Vector3<T>& aMax);

		void				InitWithMinAndMax(const Vector3<T>& aMin, const Vector3<T>& aMax);
		bool				IsInside(const Vector3<T>& aPosition)	const;

		const Vector3<T>&	GetMinPoint()							const;
		const Vector3<T>&	GetMaxPoint()							const;

	private:
		Vector3<T>			myMinPoint;
		Vector3<T>			myMaxPoint;
	};

#pragma region DEFINITIONS

	template <typename T>
	AABB3D<T>::AABB3D()
		: myMinPoint{ 0.f, 0.f, 0.f }, myMaxPoint{ 0.f, 0.f, 0.f }
	{
	}

	template <typename T>
	AABB3D<T>::AABB3D(const AABB3D& aAABB3D)
		: myMinPoint{ aAABB3D.myMinPoint }, myMaxPoint{ aAABB3D.myMaxPoint }
	{
	}

	template <typename T>
	AABB3D<T>::AABB3D(const Vector3<T>& aMin, const Vector3<T>& aMax)
		: myMinPoint{ aMin }, myMaxPoint{ aMax }
	{
	}

	template <typename T>
	void AABB3D<T>::InitWithMinAndMax(const Vector3<T>& aMin, const Vector3<T>& aMax)
	{
		myMinPoint = aMin;
		myMaxPoint = aMax;
	}

	template <typename T>
	bool AABB3D<T>::IsInside(const Vector3<T>& aPosition) const
	{
		if (myMinPoint.x > aPosition.x) { return false; }
		if (myMinPoint.y > aPosition.y) { return false; }
		if (myMinPoint.z > aPosition.z) { return false; }

		if (myMaxPoint.x < aPosition.x) { return false; }
		if (myMaxPoint.y < aPosition.y) { return false; }
		if (myMaxPoint.z < aPosition.z) { return false; }

		return true;
	}

	template <typename T>
	const Vector3<T>& AABB3D<T>::GetMinPoint() const
	{
		return myMinPoint;
	}

	template <typename T>
	const Vector3<T>& AABB3D<T>::GetMaxPoint() const
	{
		return myMaxPoint;
	}

#pragma endregion DEFINITIONS
}