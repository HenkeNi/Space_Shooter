#pragma once
#include "Vector.hpp"

/* - Description: Oriented Bounding Box (2D) is essentially an AABB with a rotation - */

namespace CommonUtilities
{
	template <typename T>
	class OBB2D
	{
	public:
		OBB2D();

	private:
		Vector2<T> myCenter;
	};

#pragma region DEFINITIONS

	template <typename T>
	OBB2D<T>::OBB2D()
		: myCenter{ 0, 0 }
	{
	}

#pragma endregion DEFINITIONS
}