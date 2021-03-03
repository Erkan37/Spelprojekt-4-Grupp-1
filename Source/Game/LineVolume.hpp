/*
*	Author: Elia Rönning & Joel Schultz
*/

#include "Line.hpp"
#include <vector>

namespace Utils
{
    template<class T>
    class LineVolume
    {
    public:
        LineVolume()
            : myLineList(std::vector<Line<T>>())
        {}
        LineVolume(const std::vector<Line<T>>& aLineList)
            : myLineList(aLineList)
        {}
        void AddLine(const Line<T>& aLine)
        {
            myLineList.push_back(aLine);
        }
        bool IsInside(const Vector2<T>& aPosition)
        {
            for (Line<T>& line : myLineList)
            {
                if (!line.IsInside(aPosition))
                {
                    return false;
                }
            }

            return true;
        }

    private:
        std::vector<Line<T>> myLineList;
    };
};