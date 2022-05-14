#pragma once
#include "Line.hpp"
#include "Vector.hpp"
#include <vector>

/* - Description: LineVolume represents a convex polygon (square, triangle) - */

namespace CommonUtilities
{
	template <typename T>
	class LineVolume
	{
	public:
		LineVolume() = default;
		LineVolume(const std::vector<Line<T>>& aLineList);

		void AddLine(const Line<T>& aLine);
		bool IsInside(const Vector2<T>& aPosition);

	private:
		std::vector<Line<T>> myLineList;
	};

#pragma region DEFINITIONS

	template <typename T>
	LineVolume<T>::LineVolume(const std::vector<Line<T>>& aLineList)
	{
		myLineList = aLineList;
	}

	template <typename T>
	void LineVolume<T>::AddLine(const Line<T>& aLine)
	{
		myLineList.push_back(aLine);
	}

	/* - A point is inside a LineVolume (convex polygon) if it's inside all of the lines making up the volume - */
	template <typename T>
	bool LineVolume<T>::IsInside(const Vector2<T>& aPosition)
	{
		for (const auto& line : myLineList)
		{
			if (!line.IsInside(aPosition))
			{
				return false;
			}
		}
		return true;
	}

#pragma endregion DEFINITIONS
}