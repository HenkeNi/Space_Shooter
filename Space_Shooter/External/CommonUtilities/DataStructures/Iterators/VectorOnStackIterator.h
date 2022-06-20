#pragma once

namespace CommonUtilities
{
	template <class VectorOnStack>
	class VectorOnStackIterator
	{
	public:
		using ValueType = typename VectorOnStack::ValueType;

	public:
		VectorOnStackIterator(ValueType* aPtr);

		VectorOnStackIterator&	operator++();
		VectorOnStackIterator&	operator++(int);
		VectorOnStackIterator&	operator--();
		VectorOnStackIterator&	operator--(int);

		ValueType&				operator[](int aIndex);
		ValueType&				operator*();
		ValueType*				operator->();

		bool					operator==(const VectorOnStackIterator& aOther) const;
		bool					operator!=(const VectorOnStackIterator& aOther) const;

	private:
		ValueType*				myPtr;
	};

#pragma region METHOD_DEFINITIONS

	template <class VectorOnStack>
	VectorOnStackIterator<VectorOnStack>::VectorOnStackIterator(ValueType* aPtr)
		: myPtr{ aPtr }
	{
	}

	template <class VectorOnStack>
	VectorOnStackIterator<VectorOnStack>& VectorOnStackIterator<VectorOnStack>::operator++()
	{
		myPtr++;
		return *this;
	}

	template <class VectorOnStack>
	VectorOnStackIterator<VectorOnStack>& VectorOnStackIterator<VectorOnStack>::operator++(int)
	{
		VectorOnStackIterator iterator = *this;
		++(*this);

		return iterator;
	}

	template <class VectorOnStack>
	VectorOnStackIterator<VectorOnStack>& VectorOnStackIterator<VectorOnStack>::operator--()
	{
		myPtr--;
		return *this;
	}

	template <class VectorOnStack>
	VectorOnStackIterator<VectorOnStack>& VectorOnStackIterator<VectorOnStack>::operator--(int)
	{
		VectorOnStackIterator iterator = *this;
		--(*this);

		return iterator;
	}

	template <class VectorOnStack>
	typename VectorOnStack::ValueType& VectorOnStackIterator<VectorOnStack>::operator[](int aIndex)
	{
		return *(myPtr[aIndex]);
	}

	template <class VectorOnStack>
	typename VectorOnStack::ValueType& VectorOnStackIterator<VectorOnStack>::operator*()
	{
		return *myPtr;
	}

	template <class VectorOnStack>
	typename VectorOnStack::ValueType* VectorOnStackIterator<VectorOnStack>::operator->()
	{
		return myPtr;
	}

	template <class VectorOnStack>
	bool VectorOnStackIterator<VectorOnStack>::operator==(const VectorOnStackIterator& aOther) const
	{
		return myPtr == aOther.myPtr;
	}

	template <class VectorOnStack>
	bool VectorOnStackIterator<VectorOnStack>::operator!=(const VectorOnStackIterator& aOther) const
	{
		return !(*this == aOther);
	}

#pragma endregion METHOD_DEFINITIONS
}