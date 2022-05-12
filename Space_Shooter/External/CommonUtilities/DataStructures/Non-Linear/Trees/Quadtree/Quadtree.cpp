#include "pch.h"
#include "Quadtree.h"


namespace CommonUtilities
{
	Quadtree::Quadtree()
	{
		for (auto& childNode : m_childNodes)
			childNode = nullptr;
	}

	void Quadtree::Insert(CollisionObject* aObject)
	{

	}

	void Quadtree::Remove(CollisionObject* aObject)
	{

	}

	void Quadtree::Clear()
	{
		m_objects.clear();

		for (auto& node : m_childNodes)
		{
			if (node != nullptr)
			{
				node->Clear();

				delete node;
				node = nullptr;
			}
		}
	}

	void Quadtree::Split()
	{
		AABB2D<float> childBounds = { m_bounds.GetMinPoint() * 0.5f, m_bounds.GetMaxPoint() * 0.5f };

		m_childNodes[0] = new Quadtree(); // TODO: Fix...
		m_childNodes[1] = new Quadtree();
		m_childNodes[2] = new Quadtree();
		m_childNodes[3] = new Quadtree();
	}

	void Quadtree::Search()
	{

	}

	int	Quadtree::GetIndex() const
	{
		return -1;
	}

	AABB2D<float> Quadtree::GetBounds() const
	{
		return {};
	}
}