/*
*	Author: Elia Rönning, Joel Schultz
*/

#pragma once

namespace Utils
{
	template <class T>
	class DoublyLinkedList;

	template <class T>
	class DoublyLinkedListNode
	{
	public:

		DoublyLinkedListNode<T>(const DoublyLinkedListNode<T>&) = delete;
		DoublyLinkedListNode<T>& operator=(const DoublyLinkedListNode<T>&) =
			delete;

		const T& GetValue() const
		{
			return myValue;
		}

		T& GetValue()
		{
			return myValue;
		}

		DoublyLinkedListNode<T>* GetNext() const
		{
			return myNext;
		}

		DoublyLinkedListNode<T>* GetPrevious() const
		{
			return myPrevious;
		}

	private:
		friend class DoublyLinkedList<T>;

		DoublyLinkedListNode(const T& aValue)
			: myValue(aValue),
			myNext(nullptr),
			myPrevious(nullptr)
		{}

		~DoublyLinkedListNode()
		{
			if (myNext)
			{
				delete myNext;
				myNext = nullptr;
			}
		}

		T myValue;
		DoublyLinkedListNode<T>* myNext;
		DoublyLinkedListNode<T>* myPrevious;
	};
}