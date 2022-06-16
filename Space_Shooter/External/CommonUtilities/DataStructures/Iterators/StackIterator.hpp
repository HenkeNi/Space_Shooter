#pragma once

namespace CommonUtilities
{
	template <class Stack>
	class StackIterator
	{
	public:
		using ValueType = typename Stack::ValueType;

	public:
		StackIterator(ValueType* aPtr);

		StackIterator&	operator++();
		StackIterator&	operator++(int);
		StackIterator&	operator--();
		StackIterator&	operator--(int);

		ValueType&		operator[](int aIndex);
		ValueType&		operator*(); 
		ValueType*		operator->(); 
		
		bool			operator==(const StackIterator& aOther) const;
		bool			operator!=(const StackIterator& aOther) const;

	private:
		ValueType*		myPtr;
	};

#pragma region DEFINITIONS

	template <class Stack>
	StackIterator<Stack>::StackIterator(ValueType* aPtr)
		: myPtr{ aPtr } 
	{
	}

	template <class Stack>
	StackIterator<Stack>& StackIterator<Stack>::operator++()
	{
		myPtr++;
		return *this;
	}

	template <class Stack>
	StackIterator<Stack>& StackIterator<Stack>::operator++(int)
	{
		StackIterator iterator = *this;
		++(*this);

		return iterator;
	}

	template <class Stack>
	StackIterator<Stack>& StackIterator<Stack>::operator--()
	{
		myPtr--;
		return *this;
	}
	
	template <class Stack>
	StackIterator<Stack>& StackIterator<Stack>::operator--(int)
	{
		StackIterator iterator = *this;
		--(*this);

		return iterator;
	}

	template <class Stack>
	typename Stack::ValueType& StackIterator<Stack>::operator[](int aIndex)
	{
		return *(myPtr[aIndex]);
	}

	template <class Stack>
	typename Stack::ValueType& StackIterator<Stack>::operator*()
	{
		return *myPtr;
	}

	template <class Stack>
	typename Stack::ValueType* StackIterator<Stack>::operator->()
	{
		return myPtr;
	}

	template <class Stack>
	bool StackIterator<Stack>::operator==(const StackIterator& aOther) const
	{
		return myPtr == aOther.myPtr;
	}

	template <class Stack>
	bool StackIterator<Stack>::operator!=(const StackIterator& aOther) const
	{
		return !(*this == aOther);
	}

#pragma endregion DEFINITIONS
}