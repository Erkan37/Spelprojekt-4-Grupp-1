/*
*	Author: Elia Rönning
*/

#ifndef VECTORONSTACK_H_
#define VECTORONSTACK_H_

#include <iostream>
#include <assert.h>

namespace Utils
{
    template<typename T, size_t size, typename counterType = uint16_t, bool safeMode = true>
    class VectorOnStack
    {
    public:
        VectorOnStack()
            : myEnd(0U)
            , mySize(size)
        {}

        VectorOnStack(const std::initializer_list<T>& anInitializerList)
            : myEnd(0U)
            , mySize(size)
        {
            assert(size >= anInitializerList.size());

            for (size_t index = 0; index < anInitializerList.size(); ++index)
            {
                Add(*(anInitializerList.begin() + index));
            }
        }

        VectorOnStack(const VectorOnStack& aVectorOnStack)
        {
            mySize = size;
            myEnd = 0U;

            assert(aVectorOnStack.Size() <= size);

            if (safeMode)
            {
                myEnd = 0U;
                for (size_t index = 0U; index < aVectorOnStack.Size(); ++index)
                {
                    Add(aVectorOnStack[static_cast<counterType>(index)]);
                }
            }
            else
            {
                memcpy(this, &aVectorOnStack, sizeof(aVectorOnStack));
            }
        }

        ~VectorOnStack()
        {
            myEnd = 0U;
            mySize = 0U;
        }

        VectorOnStack& operator=(const VectorOnStack& aVectorOnStack)
        {
            assert(aVectorOnStack.Size() <= size);

            if (safeMode)
            {
                myEnd = 0U;
                for (size_t index = 0U; index < aVectorOnStack.Size(); ++index)
                {
                    Add(aVectorOnStack[static_cast<counterType>(index)]);
                }
            }
            else
            {
                memcpy(this, &aVectorOnStack, sizeof(aVectorOnStack));
            }
        
            return *this;
        }

        inline T& operator[](const counterType& anIndex)
        {
            assert(anIndex >= 0 && anIndex < myEnd);

            return myData[anIndex];
        }

        inline const T& operator[](const counterType& anIndex) const
        {
            assert(anIndex >= 0 && anIndex < myEnd);

            return myData[anIndex];
        }

        inline VectorOnStack& Add(const T& aObject)
        {
            assert(myEnd < size);

            myData[myEnd++] = aObject;

            return *this;
        }

        inline VectorOnStack& Insert(const counterType& anIndex, const T& anObject)
        {
            assert(myEnd < size && anIndex <= myEnd);


            if (safeMode)
            {
                for (size_t index = static_cast<size_t>(myEnd); anIndex < index; --index)
                {
                    myData[index] = myData[index - 1];
                }
            }
            else
            {
                memcpy(myData + anIndex + 1, myData + anIndex, myEnd - anIndex + 1);
            }

            myData[anIndex] = anObject;

            ++myEnd;
        
            return *this;
        }

        inline VectorOnStack& RemoveCyclic(const T& anObject)
        {
            for (uint64_t index = 0U; index <= myEnd; ++index)
            {
                if (myData[index] == anObject)
                {
                    myData[index] = myData[myEnd - 1];
                }
            }

            return *this;
        }

        inline VectorOnStack& RemoveCyclicAtIndex(const counterType& anItemNumber)
        {
            myData[anItemNumber] = myData[myEnd - 1];

            return *this;
        }

        inline VectorOnStack& Clear()
        {
            myEnd = 0U;

            return *this;
        }

        __forceinline const counterType Size() const
        {
            return static_cast<counterType>(myEnd);
        }

        inline const counterType AllocatedSize() const
        {
            return static_cast<counterType>(mySize);
        }
    private:
        T myData[size];
        uint64_t myEnd;
        size_t mySize;
    };
}

#endif