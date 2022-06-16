#pragma once
#include "../CommonUtilities/DataStructures/Iterators/StackIterator.hpp"
#include <cassert>

namespace CommonUtilities
{
	template <class T, bool Static = true, typename SizeType = unsigned int>
	class Stack
	{
	public:
		using ValueType = T;
		using Iterator = StackIterator<Stack<T>>;

	public:		
		Stack(const SizeType aCapacity = 16);
		~Stack();

		SizeType	GetSize()		const;
		SizeType    GetCapacity()	const;
		const T&	GetTop()		const;
		T&			GetTop();

		bool		IsEmpty()		const;
		bool		IsFull()		const;

		void		Push(const T& aValue);
		T			Pop();
		void		Resize(const SizeType aCapacity);
		void		Clear();

		Iterator	begin(); 
		Iterator	end(); 

	private:
		T*			myData;
		SizeType	myCapacity;
		int			myTop;
	};

#pragma region DEFINITIONS

	template <class T, bool Static, typename SizeType>
	Stack<T, Static, SizeType>::Stack(const SizeType aCapacity)
		: myData{ new T[aCapacity] }, myCapacity{ aCapacity }, myTop{ 0 }
	{
		assert(aCapacity && "Capacity of stack needs to be set to a positive value");
	}

	template <class T, bool Static, typename SizeType>
	Stack<T, Static, SizeType>::~Stack()
	{
		delete[] myData;
	}

	template <class T, bool Static, typename SizeType>
	SizeType Stack<T, Static, SizeType>::GetSize()			const
	{
		return myTop;
	}	
	
	template <class T, bool Static, typename SizeType>
	SizeType Stack<T, Static, SizeType>::GetCapacity()		const
	{
		return myCapacity;
	}

	template <class T, bool Static, typename SizeType>
	const T& Stack<T, Static, SizeType>::GetTop()			const
	{
		assert(!IsEmpty() && "Unable to get top element of an empty stack!");

		return myData[myTop - 1];
	}

	template <class T, bool Static, typename SizeType>
	T& Stack<T, Static, SizeType>::GetTop()
	{
		assert(!IsEmpty() && "Unable to get top element of an empty stack!");

		return myData[myTop - 1];
	}

	template <class T, bool Static, typename SizeType>
	bool Stack<T, Static, SizeType>::IsEmpty()				const
	{
		return myTop == 0;
	}

	template <class T, bool Static, typename SizeType>
	bool Stack<T, Static, SizeType>::IsFull()				const
	{
		return myTop == myCapacity;
	}

	template <class T, bool Static, typename SizeType>
	void Stack<T, Static, SizeType>::Push(const T& aValue)
	{
		if (IsFull() && !Static)
		{
			Resize(myCapacity * 2);
			myData[myTop++] = aValue;
		}
		else if (!IsFull())
		{
			myData[myTop++] = aValue;
		}
	}
	
	template <class T, bool Static, typename SizeType>
	T Stack<T, Static, SizeType>::Pop()
	{
		assert(!IsEmpty() && "Unable to Pop an empty structure!");

		return myData[myTop--];
	}
	
	template <class T, bool Static, typename SizeType>
	void Stack<T, Static, SizeType>::Resize(const SizeType aCapacity)
	{
		assert(!Static && "Stack is not a dynamic structure!");

		T* temp = new T[aCapacity];
		for (int i = 0; i < myTop; ++i)
		{
			temp[i] = myData[i];
		}
		
		delete[] myData;
		myData = temp;

		myCapacity = aCapacity;
	}

	template <class T, bool Static, typename SizeType>
	void Stack<T, Static, SizeType>::Clear()
	{
		myTop = 0;
	}

	template<class T, bool Static, typename SizeType>
	StackIterator<Stack<T>> Stack<T, Static, SizeType>::begin()
	{
		return Iterator(myData);
	}

	template<class T, bool Static, typename SizeType>
	StackIterator<Stack<T>> Stack<T, Static, SizeType>::end()
	{
		return Iterator(myData + myTop);
	}

#pragma endregion DEFINITIONS
}