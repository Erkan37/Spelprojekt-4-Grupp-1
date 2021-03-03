/*
*	Author: Elia Rönning, Joel Schultz
*/

#pragma once
#include "DoublyLinkedListNode.hpp"

namespace Utils
{
	template <class T>
	class DoublyLinkedList
	{
	public:
		DoublyLinkedList()
			: mySize(0)
			, myHead(nullptr)
			, myTail(nullptr)
		{}

		~DoublyLinkedList()
		{
			delete myHead;
			myHead = nullptr;
			myTail = nullptr;
			mySize = 0;
		}

		const int& GetSize() const
		{
			return mySize;
		}

		DoublyLinkedListNode<T>* GetFirst()
		{
			return myHead;
		}

		DoublyLinkedListNode<T>* GetLast()
		{
			return myTail;
		}

		void InsertFirst(const T& aValue)
		{
			DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(aValue);
			if(myHead)
			{
				myHead->myPrevious = newNode;
				newNode->myNext = myHead;
			}
			if (mySize < 1)
			{
				myTail = newNode;
			}
			myHead = newNode;
			++mySize;
			
		}

		void InsertLast(const T& aValue)
		{
			DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(aValue);
			if (myTail)
			{
				myTail->myNext = newNode;
				newNode->myPrevious = myTail;
			}
			if (mySize < 1)
			{
				myHead = newNode;
			}
			myTail = newNode;

			++mySize;
		}

		void InsertBefore(DoublyLinkedListNode<T>* aNode, const T& aValue)
		{
			if (aNode == myHead)
			{
				InsertFirst(aValue);
				return;
			}

			DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(aValue);
			newNode->myPrevious = aNode->myPrevious;
			newNode->myNext = aNode;
			aNode->myPrevious->myNext = newNode;
			aNode->myPrevious = newNode;

			++mySize;
		}

		void InsertAfter(DoublyLinkedListNode<T>* aNode, const T& aValue)
		{
			if(aNode == myTail)
			{
				InsertLast(aValue);
				return;
			}

			DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>(aValue);
			newNode->myNext = aNode->myNext;
			newNode->myPrevious = aNode;
			aNode->myNext->myPrevious = newNode;
			aNode->myNext = newNode;

			++mySize;
		}

		void Remove(DoublyLinkedListNode<T>* aNode)
		{
			if (aNode == myHead)
			{
				myHead = aNode->myNext;
			}
			else
			{
				aNode->myPrevious->myNext = aNode->myNext;
			}

			if (aNode == myTail)
			{
				myTail= aNode->myPrevious;
			}
			else
			{
				aNode->myNext->myPrevious = aNode->myPrevious;
			}

			aNode->myNext = nullptr;

			delete aNode;
			--mySize;
		}
		
		DoublyLinkedListNode<T>* FindFirst(const T& aValue)
		{
			DoublyLinkedListNode<T>* currentNode = myHead;

			while (currentNode)
			{
				if (currentNode->GetValue() == aValue)
				{
					return currentNode;
				}

				currentNode = currentNode->myNext;
			}

			return nullptr;
		}
		
		DoublyLinkedListNode<T>* FindLast(const T& aValue)
		{
			DoublyLinkedListNode<T>* currentNode = myTail;

			while (currentNode)
			{
				if (currentNode->GetValue() == aValue)
				{
					return currentNode;
				}

				currentNode = currentNode->myPrevious;
			}

			return nullptr;
		}
		
		bool RemoveFirst(const T& aValue)
		{
		
			DoublyLinkedListNode<T>* currentNode = myHead;

			while (currentNode)
			{
				if (currentNode->GetValue() == aValue)
				{
					Remove(currentNode);
					return true;
				}

				currentNode = currentNode->myNext;
			}

			return false;
		}
		
		bool RemoveLast(const T& aValue)
		{
			DoublyLinkedListNode<T>* currentNode = myTail;

			while (currentNode)
			{
				if (currentNode->GetValue() == aValue)
				{
					Remove(currentNode);
					return true;
				}

				currentNode = currentNode->myPrevious;
			}

			return false;
		}

	private:
		int mySize;
		DoublyLinkedListNode<T>* myHead;
		DoublyLinkedListNode<T>* myTail;
	};
}