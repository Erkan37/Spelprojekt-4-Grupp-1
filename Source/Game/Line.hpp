/*
*	Author: Elia Rönning & Joel Schultz
*/

#include "Vector2.hpp"

namespace Utils
{
    template<class T>
    class Line
    {
    public:
        Line()
            : myOrigin(Vector2<T>(0, 0))
            , myDirection(Vector2<T>(0, 0))
        {}
        Line(const Line <T>& aLine)
            : myOrigin(aLine.myOrigin)
            , myDirection(aLine.myDirection)
        {}
        Line(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
            : myOrigin(aPoint0)
            , myDirection(aPoint1 - aPoint0)
        {}
        void InitWith2Points(const Vector2<T>& aPoint0, const Vector2<T>& aPoint1)
        {
            myOrigin = aPoint0;
            myDirection = aPoint1 - aPoint0;
        }
        void InitWithPointAndDirection(const Vector2<T>& aPoint, const Vector2<T>& aDirection)
        {
            myOrigin = aPoint;
            myDirection = aDirection;
        }
        bool IsInside(const Vector2<T>& aPosition) const
        {
            return GetNormal().Dot(aPosition - myOrigin) <= 0;
        }
        const Vector2<T>& GetDirection() const
        {
            return myDirection;
        }
        const Vector2<T> GetNormal() const
        {
            return Vector2<T>(-myDirection.y, myDirection.x);
        }

        Vector2<T> myOrigin;
        Vector2<T> myDirection;
    };
};