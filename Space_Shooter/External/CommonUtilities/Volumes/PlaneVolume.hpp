#pragma once
#include "Plane.hpp"
#include "Vector.hpp"
#include <vector>


namespace CommonUtilities
{
	/* - A PlaneVolume object represents a convex polyhedron (quad, pyramid, etc.) - */
	template <typename T>
	class PlaneVolume
	{
	public:
		PlaneVolume() = default;
		PlaneVolume(const std::vector<Plane<T>>& aPlaneList);

		void AddPlane(const Plane<T>& aPlane);
		bool IsInside(const Vector3<T>& aPosition);

	private:
		std::vector<Plane<T>> myPlaneList;
	};

#pragma region DEFINITIONS

	template <typename T>
	PlaneVolume<T>::PlaneVolume(const std::vector<Plane<T>>& aPlaneList)
	{
		myPlaneList = aPlaneList;
	}

	template <typename T>
	void PlaneVolume<T>::AddPlane(const Plane<T>& aPlane)
	{
		myPlaneList.push_back(aPlane);
	}

	/* - A point is inside a PlaneVolume if it's inside all of the planes making up the volume  - */
	template <typename T>
	bool PlaneVolume<T>::IsInside(const Vector3<T>& aPosition)
	{
		for (const auto& plane : myPlaneList)
		{
			if (!plane.IsInside(aPosition))
			{
				return false;
			}
		}
		return true;
	}

#pragma endregion DEFINITIONS
}