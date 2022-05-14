#pragma once
#include "Vector.hpp"

/* - Description: a ray is defined by a point of origin and a direction. Similar to a Line, but is only infinite in one direction - */

namespace CommonUtilities
{
	template <typename T>
	class Ray
	{
	public:
		Ray();
		Ray(const Ray& aRay);
		Ray(const Vector3<T>& anOrigin, const Vector3<T>& aPoint);

		void				InitWith2Points(const Vector3<T>& anOrigin, const Vector3<T>& aPoint);
		void				InitWithOriginAndDirection(const Vector3<T>& anOrigin, const Vector3<T>& aDirection);

		const Vector3<T>&	GetOrigin()		const;
		const Vector3<T>&	GetDirection()	const;

	private:
		Vector3<T>			myOrigin;
		Vector3<T>			myDirection;
	};

#pragma region DEFINITIONS

	template <typename T>
	Ray<T>::Ray()
		: myOrigin{ 0.f, 0.f, 0.f }, myDirection{ 0.f, 0.f, 0.f }
	{
	}

	template <typename T>
	Ray<T>::Ray(const Ray& aRay)
		: myOrigin{ aRay.myOrigin }, myDirection{ aRay.myDirection }
	{
	}

	template <typename T>
	Ray<T>::Ray(const Vector3<T>& anOrigin, const Vector3<T>& aPoint)
		: myOrigin{ anOrigin }, myDirection{ aPoint - anOrigin }
	{
	}

	template <typename T>
	void Ray<T>::InitWith2Points(const Vector3<T>& anOrigin, const Vector3<T>& aPoint)
	{
		myOrigin = anOrigin;
		myDirection = aPoint - anOrigin;
	}

	template <typename T>
	void Ray<T>::InitWithOriginAndDirection(const Vector3<T>& anOrigin, const Vector3<T>& aDirection)
	{
		myOrigin = anOrigin;
		myDirection = aDirection;
	}

	template <typename T>
	const Vector3<T>& Ray<T>::GetOrigin() const
	{
		return myOrigin;
	}

	template <typename T>
	const Vector3<T>& Ray<T>::GetDirection() const
	{
		return myDirection;
	}

#pragma endregion DEFINITIONS
}