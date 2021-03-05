/*
*	Author: Elia Rönning
*/

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "Keys.h"

#include <iostream>
#include <chrono>
#include <assert.h>
#include <Windows.h>
#include <map>

namespace Utils
{
    class Input
    {
    public:
        Input();
        Input(const Input& anInput) = delete;
        ~Input() = default;

        Input& Update();
        bool UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam);
        bool GetKeyDown(const Keys& aKey);
        bool GetKeyJustDown(const Keys& aKey);
        bool GetKeyJustUp(const Keys& aKey);
        POINT GetMousePosition() const;
        POINT GetMouseMovementSinceLastUpdate() const;
        Input& SetAbsoluteMousePosition(const POINT& aPoint);
        Input& SetMousePosition(const POINT& aPoint);
        Input& ToggleCaptureCursor();

        const std::string KeyToString(const Keys& aKey);

    private:
        static const std::string ourUndefined;
        static const std::map<Keys, std::string> ourKeyToString;
        bool ValidateKey(const Keys& aKey);

        std::map<Keys, bool> myKeyMap;
        std::map<Keys, bool> myLastKeyMap;
        std::map<Keys, bool> myMessageMap;

        POINT myMousePosition;
        POINT myLastMousePosition;

        bool myMouseIsCaptured;
    };
    class Timer
    {
    public:
        Timer();
        Timer(const Timer& aTimer) = delete;
        Timer& operator=(const Timer& aTimer) = delete;

        Timer& Update();

        const float GetDeltaTime() const;
        const double GetTotalTime() const;

        const void SetFreezeTime(const bool aFreezeState);

    private:
        static constexpr int ourNanoSecondsToSeconds = 1000000000;
        static constexpr double ourInverseNanoSecondsToSeconds = 1.0 / (double)ourNanoSecondsToSeconds;

        std::chrono::high_resolution_clock myClock;
        const uint64_t myStartTime;
        uint64_t myLastUpdate;
        uint64_t myCurrentTime;
        bool myFreezeTime;
    };

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

    template<typename T>
    const T& Max(const T& aFirst, const T& aSecond)
    {
        return (aFirst > aSecond) ? aFirst : aSecond;
    }

    template<typename T>
    const T& Min(const T& aFirst, const T& aSecond)
    {
        return (aFirst < aSecond) ? aFirst : aSecond;
    }

    template<typename T>
    const T Abs(const T& aNumber)
    {
        return (aNumber > 0) ? aNumber : aNumber * -1;
    }

    template<typename T>
    const T& Clamp(const T& aValue, const T& aMin, const T& aMax)
    {
        if (aMin > aMax)
        {
            std::cerr << "Clamp: aMax is bigger than aMin" << std::endl;
        }

        return (aValue >= aMax) ? aMax : ((aValue <= aMin) ? aMin : aValue);
    }

    template<typename T>
    const T Lerp(const T& aFirst, const T& aSecond, const float aPercentage)
    {
        return static_cast<T>(aFirst + (aPercentage * (aSecond - aFirst)));
    }

    template<typename T>
    void Swap(T& aFirst, T& aSecond)
    {
        T temp = aFirst;
        aFirst = aSecond;
        aSecond = temp;
    }
}

#endif