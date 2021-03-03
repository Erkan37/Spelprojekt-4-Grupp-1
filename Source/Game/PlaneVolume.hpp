/*
*	Author: Elia Rönning & Joel Schultz
*/

#include "Plane.hpp"
#include <vector>

namespace Utils
{
    template<class T>
    class PlaneVolume
    {
    public:
        PlaneVolume()
            : myPlaneList(std::vector<Plane<T>>())
        {}
        PlaneVolume(const std::vector<Plane<T>>& aPlaneList)
            : myPlaneList(aPlaneList)
        {}
        void AddPlane(const Plane<T>& aPlane)
        {
            myPlaneList.push_back(aPlane);
        }
        bool IsInside(const Vector3<T>& aPosition)
        {
            for (Plane<T>& plane : myPlaneList)
            {
                if (!plane.IsInside(aPosition))
                {
                    return false;
                }
            }

            return true;
        }

    private:
        std::vector<Plane<T>> myPlaneList;    
    };
};