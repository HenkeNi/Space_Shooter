#pragma once
#include "Volumes.hpp"
#include "Vector.hpp"
#include "UtilityFunctions.hpp"
#include <algorithm>


namespace CommonUtilities
{
	/***************************************************************************************************/
	/*										2D - Intersections   									   */
	/***************************************************************************************************/

#pragma region INTERSECTIONS_2D

	/* ----------------------------- AABB2D vs AABB2D ---------------------------- */
	template <typename T>
	bool IntersectionAABB2DVsAABB2D(const AABB2D<T>& aAABB1, const AABB2D<T>& aAABB2)
	{
		if (aAABB1.GetMaxPoint().x < aAABB2.GetMinPoint().x) { return false; }
		if (aAABB1.GetMaxPoint().y < aAABB2.GetMinPoint().y) { return false; }

		if (aAABB1.GetMinPoint().x > aAABB2.GetMaxPoint().x) { return false; }
		if (aAABB1.GetMinPoint().y > aAABB2.GetMaxPoint().y) { return false; }

		return true;
	}

	/* ----------------------------- AABB2D vs Circle ---------------------------- */
	template <typename T>
	bool IntersectionAABB2DVsCircle(const AABB2D<T>& aAABB, const Circle<T>& aCircle)
	{
		float deltaX = aCircle.GetCenterPosition().x - std::max(aAABB.GetMinPoint().x, std::min(aCircle.GetCenterPosition().x, aAABB.GetMaxPoint().x));
		float deltaY = aCircle.GetCenterPosition().y - std::max(aAABB.GetMinPoint().y, std::min(aCircle.GetCenterPosition().y, aAABB.GetMaxPoint().y));

		return ((deltaX * deltaX) + (deltaY * deltaY)) < (aCircle.GetRadius() * aCircle.GetRadius());
	}

	/* ----------------------------- AABB2D vs Point ----------------------------- */
	template <typename T>
	bool IntersectionAABB2DVsPoint(const AABB2D<T>& aAABB, const Vector2<T>& aPoint)
	{
		return aAABB.IsInside(aPoint);
	}

	/* ----------------------------- Circle vs Circle ---------------------------- */
	template <typename T>
	bool IntersectionCircleVsCircle(const Circle<T>& aCircle1, const Circle<T>& aCircle2)
	{
		Vector2<T> distance = (aCircle2.GetCenterPosition() - aCircle1.GetCenterPosition());
		float length = distance.LengthSqr();

		return length <= (aCircle1.GetRadius() + aCircle2.GetRadius()) * (aCircle1.GetRadius() + aCircle2.GetRadius());
	}



	/* ----------------------------- AABB2D vs AABB2 Sweap ----------------------- */
	template <typename T>
	bool IntersectionAABB2DVsAABB2DSweap(const AABB2D<T>& aAABB1, const AABB2D<T>& aAABB2, const Vector2<float>& aVelocity)
	{
		return false;
	}

	/* ----------------------------- Circle vs Line ------------------------------ */
	template <typename T>
	bool IntersectionCircleVsLine(const Circle<T>& aCircle, const Line<T>& aLine)
	{
		return false;
	}

	/* ----------------------------- AABB2D vs Line ------------------------------ */
	template <typename T>
	bool IntersectionAABB2DVsLine(const AABB2D<T>& aAABB, const Line<T>& aLine)
	{
		return false;
	}

	/* ----------------------------- Line vs Line -------------------------------- */
	template <typename T>
	bool IntersectionLineVsLine(const Line<T>& aLine1, const Line<T>& aLine2)
	{
		return false;
	}

	// TODO: RAY? z == 0.f..

#pragma endregion INTERSECTIONS_2D

	/***************************************************************************************************/
	/*										3D - Intersections   									   */
	/***************************************************************************************************/

#pragma region INTERSECTIONS_3D

	/* ----------------------------- AABB3D vs AABB3D ---------------------------- */
	template <typename T>
	bool IntersectionAABB3DVsAABB3D(const AABB3D<T>& aAABB3D1, const AABB3D<T>& aAABB3D2)
	{
		if (aAABB3D1.myMaxPoint.x < aAABB3D2.myMinPoint.x) { return false; }
		if (aAABB3D1.myMaxPoint.y < aAABB3D2.myMinPoint.y) { return false; }
		if (aAABB3D1.myMaxPoint.z < aAABB3D2.myMinPoint.z) { return false; }

		if (aAABB3D1.myMinPoint.x > aAABB3D2.myMaxPoint.x) { return false; }
		if (aAABB3D1.myMinPoint.y > aAABB3D2.myMaxPoint.y) { return false; }
		if (aAABB3D1.myMinPoint.z > aAABB3D2.myMaxPoint.z) { return false; }

		return true;
	}

	/* ----------------------------- Ray vs AABB3D ------------------------------- */
	template <typename T>
	bool IntersectionRayVsAABB3D(const Ray<T>& aRay, const AABB3D<T>& aAABB)
	{
		T tMin = (aAABB.GetMinPoint().x - aRay.GetOrigin().x) / aRay.GetDirection().x;
		T tMax = (aAABB.GetMaxPoint().x - aRay.GetOrigin().x) / aRay.GetDirection().x;

		if (tMin > tMax)
		{
			std::swap(tMin, tMax);
		}

		T tyMin = (aAABB.GetMinPoint().y - aRay.GetOrigin().y) / aRay.GetDirection().y;
		T tyMax = (aAABB.GetMaxPoint().y - aRay.GetOrigin().y) / aRay.GetDirection().y;

		if (tyMin > tyMax)
		{
			std::swap(tyMin, tyMax);
		}

		if (tyMin > tMin)
		{
			tMin = tyMin;
		}

		if (tyMax < tMax)
		{
			tMax = tyMax;
		}

		T tzMin = (aAABB.GetMinPoint().z - aRay.GetOrigin().z) / aRay.GetDirection().z;
		T tzMax = (aAABB.GetMaxPoint().z - aRay.GetOrigin().z) / aRay.GetDirection().z;

		if (tzMin > tyMax)
		{
			std::swap(tzMin, tzMax);
		}

		if ((tMin >= tzMax) || (tzMin >= tMax))
		{
			return false;
		}

		if (tzMax > tMin)
		{
			tMin = tzMin;
		}

		if (tzMax < tMax)
		{
			tMax = tzMax;
		}

		return true;
	}

	/* ----------------------------- Ray vs Sphere ------------------------------- */
	template <typename T>
	bool IntersectionRayVsSphere(const Ray<T>& aRay, const Sphere<T>& aSphere)
	{
		Vector3<T> myClosestPoint = aRay.GetOrigin() + aRay.GetDirection() * ((aSphere.GetCenterPosition() - aRay.GetOrigin()).Dot(aRay.GetDirection()));
		return (myClosestPoint - aSphere.GetCenterPosition()).LengthSqr() <= aSphere.GetRadius() * aSphere.GetRadius();
	}

	/* ----------------------------- Ray vs Plane -------------------------------- */
	template <typename T>
	bool IntersectionRayVsPlane(const Ray<T>& aRay, const Plane<T>& aPlane, Vector3<T>& aOutIntersectionPoint)
	{
		T denom = aPlane.GetNormal().Dot(aRay.GetDirection().GetNormalized());
		if (std::abs(denom) > 0)
		{
			Vector3<T> point = aPlane.GetPoint() - aRay.GetOrigin();
			if (point.Dot(aPlane.GetNormal()) >= 0)
			{
				aOutIntersectionPoint = point;
				return true;
			}
		}
		return false;
	}

	/* ----------------------------- Ray vs Ray ---------------------------------- */
	template <typename T>
	bool IntersectionRayVsRay(const Ray<T>& aRay1, const Ray<T>& aRay2)
	{
		return false;
	}

	/* ----------------------------- Sphere vs AABB3D ---------------------------- */
	template <typename T>
	bool IntersectionSphereVsAABB3D(const Sphere<T>& aSphere, const AABB3D<T>& aAABB3D)
	{
		return false;
	}

	/* ----------------------------- Sphere vs Sphere ---------------------------- */
	template <typename T>
	bool IntersectionSphereVsSphere(const Sphere<T>& aSphere1, const Sphere<T>& aSphere2)
	{
		Vector3<T> distance = aSphere2.GetCenterPosition() - aSphere1.GetCenterPosition();
		return distance.LengthSqr() <= (aSphere1.GetRadius() + aSphere2.GetRadius());
	}

	/* ----------------------------- Point vs Sphere ----------------------------- */
	template <typename T>
	bool IntersectionPointVsSphere(const Vector3<T>& aPoint, const Sphere<T>& aSphere)
	{
		return aSphere.IsInside(aPoint);
	}

	/* ----------------------------- Point vs AABB ------------------------------- */
	template <typename T>
	bool IntersectionPointVsAABB(const Vector3<T>& aPoint, const AABB3D<T>& aAABB3D)
	{
		return aAABB3D.IsInside(aPoint);
	}

	/* ----------------------------- Plane vs Sphere ----------------------------- */
	template <typename T>
	bool IntersectionPlaneVsSphere(const Plane<T>& aPlane, const Sphere<T>& aSphere)
	{
		return false;

	}

#pragma endregion INTERSECTIONS_3D
}