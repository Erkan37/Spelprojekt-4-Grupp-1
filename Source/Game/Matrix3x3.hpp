/*
*	Author: Elia Rönning & Joel Schultz
*/

#pragma once

#include <assert.h>
#include <math.h>
#include "Matrix4x4.hpp"
#include "Vector3.hpp"

namespace Utils
{
    template <class T>
    class Matrix3x3
    {
    public:
        Matrix3x3<T>()
            : myData()
        {
            myData[0] = 1;
            myData[4] = 1;
            myData[8] = 1;
        }
        Matrix3x3<T>(const Matrix3x3<T>& aMatrix)
        {
            for (int index = 0; index < 9; ++index)
            {
                int row = (index - (index % 3)) / 3 + 1;
                int column = index % 3 + 1;

                myData[index] = aMatrix(row, column);
            }
        }
        Matrix3x3<T>(const Matrix4x4<T>& aMatrix)
        {
            for (int index = 0; index < 9; ++index)
            {
                int row = (index - (index % 3)) / 3 + 1;
                int column = index % 3 + 1;

                myData[index] = aMatrix(row, column);
            }
        }

        T& operator()(const int aRow, const int aColumn)
        {
            assert(aRow <= 3 && aRow > 0);
            assert(aColumn <= 3 && aColumn > 0);

            return myData[((aRow - 1) * 3) + (aColumn - 1)];
        }
        const T& operator()(const int aRow, const int aColumn) const
        {
            assert(aRow <= 3 && aRow > 0);
            assert(aColumn <= 3 && aColumn > 0);

            return myData[((aRow - 1) * 3) + (aColumn - 1)];
        }

        const Matrix3x3<T> operator+(const Matrix3x3<T>& aMatrix) const
        {
            Matrix3x3<T> newMatrix;
            for (int index = 0; index < 9; ++index)
            {
                int row = (index - (index % 3)) / 3 + 1;
                int column = index % 3 + 1;

                newMatrix(row, column) = myData[index] + aMatrix(row, column);
            }
            return newMatrix;
        }
        const Matrix3x3<T> operator-(const Matrix3x3<T>& aMatrix) const
        {
            Matrix3x3<T> newMatrix;
            for (int index = 0; index < 9; ++index)
            {
                int row = (index - (index % 3)) / 3 + 1;
                int column = index % 3 + 1;

                newMatrix(row, column) = myData[index] - aMatrix(row, column);
            }
            return newMatrix;
        }
        Matrix3x3<T>& operator+=(const Matrix3x3<T>& aMatrix)
        {
            for (int index = 0; index < 9; ++index)
            {
                int row = (index - (index % 3)) / 3 + 1;
                int column = index % 3 + 1;

                myData[index] += aMatrix(row, column);
            }

            return *this;
        }
        Matrix3x3<T>& operator-=(const Matrix3x3<T>& aMatrix)
        {
            for (int index = 0; index < 9; ++index)
            {
                int row = (index - (index % 3)) / 3 + 1;
                int column = index % 3 + 1;

                myData[index] -= aMatrix(row, column);
            }

            return *this;
        }
        void operator=(const Matrix3x3<T>& aMatrix)
        {
            for (int index = 0; index < 9; ++index)
            {
                int row = (index - (index % 3)) / 3 + 1;
                int column = index % 3 + 1;

                myData[index] = aMatrix(row, column);
            }
        }
        Matrix3x3<T> operator*(const Matrix3x3<T>& aMatrix)
        {
            Matrix3x3<T> matrix;
            
            matrix(1, 1) = myData[0] * aMatrix(1, 1) + myData[1] * aMatrix(2, 1) + myData[2] * aMatrix(3, 1);
            matrix(1, 2) = myData[0] * aMatrix(1, 2) + myData[1] * aMatrix(2, 2) + myData[2] * aMatrix(3, 2);
            matrix(1, 3) = myData[0] * aMatrix(1, 3) + myData[1] * aMatrix(2, 3) + myData[2] * aMatrix(3, 3);
            
            matrix(2, 1) = myData[3] * aMatrix(1, 1) + myData[4] * aMatrix(2, 1) + myData[5] * aMatrix(3, 1);
            matrix(2, 2) = myData[3] * aMatrix(1, 2) + myData[4] * aMatrix(2, 2) + myData[5] * aMatrix(3, 2);
            matrix(2, 3) = myData[3] * aMatrix(1, 3) + myData[4] * aMatrix(2, 3) + myData[5] * aMatrix(3, 3);
            
            matrix(3, 1) = myData[6] * aMatrix(1, 1) + myData[7] * aMatrix(2, 1) + myData[8] * aMatrix(3, 1);
            matrix(3, 2) = myData[6] * aMatrix(1, 2) + myData[7] * aMatrix(2, 2) + myData[8] * aMatrix(3, 2);
            matrix(3, 3) = myData[6] * aMatrix(1, 3) + myData[7] * aMatrix(2, 3) + myData[8] * aMatrix(3, 3);

            return matrix;
        }
        Matrix3x3<T>& operator*=(const Matrix3x3<T>& aMatrix)
        {
            (*this) = (*this) * aMatrix;

            return *this;
        }

        static Matrix3x3<T> CreateRotationAroundX(T anAngleInRadians)
        {
            Matrix3x3<T> matrix;

            matrix(2, 2) = cos(anAngleInRadians);
            matrix(2, 3) = sin(anAngleInRadians);
            matrix(3, 2) = -matrix(2, 3);
            matrix(3, 3) = matrix(2, 2);

            return matrix;
        }
        static Matrix3x3<T> CreateRotationAroundY(T anAngleInRadians)
        {
            Matrix3x3<T> matrix;

            matrix(1, 1) = cos(anAngleInRadians);
            matrix(3, 1) = sin(anAngleInRadians);
            matrix(1, 3) = -matrix(3, 1);
            matrix(3, 3) = matrix(1, 1);

            return matrix;
        }
        static Matrix3x3<T> CreateRotationAroundZ(T anAngleInRadians)
        {
            Matrix3x3<T> matrix;

            matrix(1, 1) = cos(anAngleInRadians);
            matrix(1, 2) = sin(anAngleInRadians);
            matrix(2, 1) = -matrix(1, 2);
            matrix(2, 2) = matrix(1, 1);

            return matrix;
        }

        static Matrix3x3<T> Transpose(const Matrix3x3<T>& aMatrixToTranspose)
        {
            Matrix3x3<T> matrix;

            for (int index = 0; index < 9; ++index)
            {
                int row = (index - (index % 3)) / 3 + 1;
                int column = index % 3 + 1;

                matrix(row, column) = aMatrixToTranspose(column, row);
            }

            return matrix;
        }
    private:
        T myData[9];
    };
};

template <class T>
Utils::Vector3<T> operator*(const Utils::Vector3<T>& aVector, const Utils::Matrix3x3<T>& aMatrix)
{
    Utils::Vector3<T> vec;

    vec.x = CommonUtilities::Vector3<T>(aMatrix(1, 1), aMatrix(2, 1), aMatrix(3, 1)).Dot(aVector);
    vec.y = CommonUtilities::Vector3<T>(aMatrix(1, 2), aMatrix(2, 2), aMatrix(3, 2)).Dot(aVector);
    vec.z = CommonUtilities::Vector3<T>(aMatrix(1, 3), aMatrix(2, 3), aMatrix(3, 3)).Dot(aVector);

    return vec;
}

template <class T>
const bool operator==(const Utils::Matrix3x3<T>& aMatrix, const Utils::Matrix3x3<T>& anotherMatrix)
{
    for (int index = 0; index < 9; ++index)
    {
        int row = (index - (index % 3)) / 3 + 1;
        int column = index % 3 + 1;

        if (aMatrix(row, column) != anotherMatrix(row, column))
        {
            return false;
        }
    }

    return true;
}

typedef Utils::Matrix3x3<float> m3f;
typedef Utils::Matrix3x3<double> m3d;
typedef Utils::Matrix3x3<int32_t> m3i;
typedef Utils::Matrix3x3<uint32_t> m3ui;