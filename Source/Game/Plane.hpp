/*
*	Author: Elia Rönning & Joel Schultz
*/

#include "Vector3.hpp"

namespace Utils
{
    template<class T>
    class Plane
    {
    public:
        Plane()
            : myPoint(Vector3<T>(0, 0, 0))
            , myNormal(Vector3<T>(0, 0, 0))
        {}
        Plane(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
            : myPoint(aPoint0)
            , myNormal(Vector3<T>(aPoint1 - aPoint0).Cross(aPoint2 - aPoint0))
        {}
        Plane(const Vector3<T>& aPoint0, const Vector3<T>& aNormal)
            : myPoint(aPoint0)
            , myNormal(aNormal)
        {}
        void InitWith3Points(const Vector3<T>& aPoint0, const Vector3<T>& aPoint1, const Vector3<T>& aPoint2)
        {
            myPoint = aPoint0;
            myNormal = Vector3<T>(aPoint1 - aPoint0).Cross(aPoint2 - aPoint0);
        }
        void InitWithPointAndNormal(const Vector3<T>& aPoint, const Vector3<T>& aNormal)
        {
            myPoint = aPoint;
            myNormal = aNormal;
        }
        bool IsInside(const Vector3<T>& aPosition) const
        {
            return myNormal.Dot(aPosition - myPoint) <= 0;
        }
        const Vector3<T>& GetNormal() const
        {
            return myNormal;
        }

        Vector3<T> myPoint;
        Vector3<T> myNormal;
    };
};