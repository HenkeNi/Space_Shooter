#pragma once
#include "../CommonUtilities/DataStructures/Iterators/VectorOnStackIterator.h"
#include <cassert>
#include <initializer_list>

// TODO: empalce back!
namespace CommonUtilities
{
	template <typename Type, int size, typename CounterType = unsigned short, bool useSafeModeFlag = true>
	class VectorOnStack
	{
	public:
		using ValueType = Type;
		using Iterator = VectorOnStackIterator<VectorOnStack<Type, size, CounterType, useSafeModeFlag>>;

	public:
		VectorOnStack();
		VectorOnStack(const VectorOnStack& aVectorOnStack);
		VectorOnStack(const std::initializer_list<Type>& aList);
		~VectorOnStack();

		VectorOnStack&	operator= (const VectorOnStack& aVectorOnStack);
		VectorOnStack&	operator= (const std::initializer_list<Type>& aList);

		Type&			operator[] (const CounterType anIndex);
		const Type&		operator[] (const CounterType anIndex)						const;

		CounterType		Size()														const;
		bool			IsEmpty()													const;
		void			Add(const Type& aType);
		void			Insert(const CounterType anIndex, const Type& anObject);
		void			RemoveCyclic(const Type& anObject);
		void			RemoveCyclicAtIndex(const CounterType anIndex);
		void			Clear();

		Iterator		begin();
		Iterator		end();

	private:
		Type			m_data[size];
		CounterType		m_counter;
	};

#pragma region METHOD_DEFINITIONS

	template <typename Type, int size, typename CounterType , bool useSafeModeFlag>
	VectorOnStack<Type, size, CounterType, useSafeModeFlag>::VectorOnStack()
		: m_counter{ 0 }
	{
	}

	template <typename Type, int size, typename CounterType , bool useSafeModeFlag>
	VectorOnStack<Type, size, CounterType, useSafeModeFlag>::VectorOnStack(const VectorOnStack& aVectorOnStack)
	{
		assert(&aVectorOnStack != this);

		if (useSafeModeFlag)
		{
			for (int i = 0; i < aVectorOnStack.Size(); ++i)
			{
				m_data[i] = aVectorOnStack.m_data[i];
			}
			m_counter = aVectorOnStack.m_counter;
		}
		else
		{
			m_counter = aVectorOnStack.m_counter > size ? size : aVectorOnStack.m_counter;
			std::memcpy(m_data, aVectorOnStack.m_data, m_counter * sizeof(Type));

		}
	}

	template <typename Type, int size, typename CounterType, bool useSafeModeFlag>
	VectorOnStack<Type, size, CounterType, useSafeModeFlag>::VectorOnStack(const std::initializer_list<Type>& aList)
	{
		assert(aList.size() <= size);
		if (useSafeModeFlag)
		{
			for (int i = 0; i < aList.size(); ++i)
			{
				m_data[m_counter++] = *(aList.begin() + i);
			}
		}
		else
		{
			m_counter = aList.size();
			std::memcpy(m_data, aList.begin(), aList.Size() * sizeof(Type));
		}
	}

	template <typename Type, int size, typename CounterType, bool useSafeModeFlag>
	VectorOnStack<Type, size, CounterType, useSafeModeFlag>::~VectorOnStack()
	{
		Clear();
	}

	template <typename Type, int size, typename CounterType, bool useSafeModeFlag>
	VectorOnStack<Type, size, CounterType, useSafeModeFlag>& VectorOnStack<Type, size, CounterType, useSafeModeFlag>::operator= (const VectorOnStack& aVectorOnStack)
	{
		if (&aVectorOnStack == this) { return *this; }

		if (useSafeModeFlag)
		{
			for (int i = 0; i < aVectorOnStack.Size(); ++i)
			{
				m_data[i] = aVectorOnStack.m_data[i];
			}
			m_counter = aVectorOnStack.m_counter;
		}
		else
		{
			m_counter = aVectorOnStack.m_counter > size ? size : aVectorOnStack.m_counter;
			std::memcpy(m_data, aVectorOnStack.m_data, m_counter * sizeof(Type));

		}
		return *this;
	}

	template <typename Type, int size, typename CounterType, bool useSafeModeFlag>
	VectorOnStack<Type, size, CounterType, useSafeModeFlag>& VectorOnStack<Type, size, CounterType, useSafeModeFlag>::operator= (const std::initializer_list<Type>& aList)
	{
		if (useSafeModeFlag)
		{
			for (int i = 0; i < aList.size(); ++i)
			{
				if (i < size)
				{
					m_data[m_counter++] = *(aList.begin() + i);
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			m_counter = aList.size() > size ? size : aList.size();
			std::memcpy(m_data, aList.begin(), m_counter * sizeof(Type));
		}
		return *this;
	}

	template <typename Type, int size, typename CounterType, bool useSafeModeFlag>
	Type& VectorOnStack<Type, size, CounterType, useSafeModeFlag>::operator[] (const CounterType anIndex)
	{
		assert(anIndex >= 0 && anIndex < m_counter);
		return m_data[anIndex];
	}

	template <typename Type, int size, typename CounterType, bool useSafeModeFlag>
	const Type& VectorOnStack<Type, size, CounterType, useSafeModeFlag>::operator[] (const CounterType anIndex) const
	{
		assert(anIndex >= 0 && anIndex < m_counter);
		return m_data[anIndex];
	}

	template <typename Type, int size, typename CounterType, bool useSafeModeFlag>
	CounterType VectorOnStack<Type, size, CounterType, useSafeModeFlag>::Size()	const
	{
		return m_counter;
	}

	template <typename Type, int size, typename CounterType, bool useSafeModeFlag>
	bool VectorOnStack<Type, size, CounterType, useSafeModeFlag>::IsEmpty()	const
	{
		return m_counter == 0;
	}

	template <typename Type, int size, typename CounterType, bool useSafeModeFlag>
	void VectorOnStack<Type, size, CounterType, useSafeModeFlag>::Add(const Type& aType)
	{
		assert(m_counter < size);
		m_data[m_counter++] = aType;
	}

	template <typename Type, int size, typename CounterType, bool useSafeModeFlag>
	void VectorOnStack<Type, size, CounterType, useSafeModeFlag>::Insert(const CounterType anIndex, const Type& anObject)
	{
		assert(m_counter < size && anIndex >= 0 && anIndex < size && anIndex < m_counter + 1);
		Type newData[size];
		if (useSafeModeFlag)
		{
			int offset = 0;
			for (int i = 0; i < size; ++i)
			{
				if (i == anIndex)
				{
					newData[anIndex] = anObject;
					offset = 1;
				}
				else
				{
					newData[i] = m_data[i - offset];
				}
			}
			++m_counter;
			for (int i = 0; i < size; ++i)
			{
				m_data[i] = newData[i];
			}
		}
		else
		{
			// Copy elements before index
			std::memcpy(newData, m_data, anIndex * sizeof(Type));

			// Insert new element at index position
			std::memcpy(newData + (anIndex), &anObject, sizeof(Type));

			// Copy elements after index position				
			int elementsLeftToCopy = size - (anIndex + 1);
			std::memcpy(newData + (anIndex + 1), m_data + anIndex, sizeof(Type) * elementsLeftToCopy);

			// Copy back elements
			std::memcpy(m_data, newData, sizeof(Type) * (++m_counter));
		}
	}

	template <typename Type, int size, typename CounterType, bool useSafeModeFlag>
	void VectorOnStack<Type, size, CounterType, useSafeModeFlag>::RemoveCyclic(const Type& anObject)
	{
		int index = -1;
		for (int i = 0; i < m_counter; ++i)
		{
			if (m_data[i] == anObject)
			{
				index = i;
				break;
			}
		}

		if (index != -1)
			m_data[index] = m_data[--m_counter];
	}

	template <typename Type, int size, typename CounterType, bool useSafeModeFlag>
	void VectorOnStack<Type, size, CounterType, useSafeModeFlag>::RemoveCyclicAtIndex(const CounterType anIndex)
	{
		assert(anIndex >= 0 && anIndex < m_counter);
		m_data[anIndex] = m_data[--m_counter];
	}

	template <typename Type, int size, typename CounterType, bool useSafeModeFlag>
	void VectorOnStack<Type, size, CounterType, useSafeModeFlag>::Clear()
	{
		m_counter = 0;
	}

	template <typename Type, int size, typename CounterType, bool useSafeModeFlag>
	VectorOnStackIterator<VectorOnStack<Type, size, CounterType, useSafeModeFlag>> VectorOnStack<Type, size, CounterType, useSafeModeFlag>::begin()
	{
		return Iterator(m_data);
	}

	template <typename Type, int size, typename CounterType, bool useSafeModeFlag>
	VectorOnStackIterator<VectorOnStack<Type, size, CounterType, useSafeModeFlag>> VectorOnStack<Type, size, CounterType, useSafeModeFlag>::end()
	{
		return Iterator(m_data + m_counter);
	}

#pragma endregion METHOD_DEFINITIONS
}