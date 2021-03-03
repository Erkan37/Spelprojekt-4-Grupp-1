/*
*	Author: Elia Rönning & Joel Schultz
*/

#pragma once
#include <assert.h>
#include "Vector4.hpp"

namespace Utils
{
    template <class T>
    class Matrix4x4
    {
    public:
        Matrix4x4<T>()
            : myData()
        {
            myData[0] = 1;
            myData[5] = 1;
            myData[10] = 1;
            myData[15] = 1;
        }
        Matrix4x4<T>(const Matrix4x4<T>& aMatrix)
        {
            for (int index = 0; index < 16; ++index)
            {
                int row = (index - (index % 4)) / 4 + 1;
                int column = index % 4 + 1;

                myData[index] = aMatrix(row, column);
            }
        }

        T& operator()(const int aRow, const int aColumn)
        {
            assert(aRow <= 4 && aRow > 0);
            assert(aColumn <= 4 && aColumn > 0);

            return myData[((aRow - 1) * 4) + (aColumn - 1)];
        }
        const T& operator()(const int aRow, const int aColumn) const
        {
            assert(aRow <= 4 && aRow > 0);
            assert(aColumn <= 4 && aColumn > 0);

            return myData[((aRow - 1) * 4) + (aColumn - 1)];
        }

        const Matrix4x4<T> operator+(const Matrix4x4<T>& aMatrix) const
        {
            Matrix4x4<T> newMatrix;
            for (int index = 0; index < 16; ++index)
            {
                int row = (index - (index % 4)) / 4 + 1;
                int column = index % 4 + 1;

                newMatrix(row, column) = myData[index] + aMatrix(row, column);
            }
            return newMatrix;
        }
        const Matrix4x4<T> operator-(const Matrix4x4<T>& aMatrix) const
        {
            Matrix4x4<T> newMatrix;
            for (int index = 0; index < 16; ++index)
            {
                int row = (index - (index % 4)) / 4 + 1;
                int column = index % 4 + 1;

                newMatrix(row, column) = myData[index] - aMatrix(row, column);
            }
            return newMatrix;
        }
        Matrix4x4<T>& operator+=(const Matrix4x4<T>& aMatrix)
        {
            for (int index = 0; index < 16; ++index)
            {
                int row = (index - (index % 4)) / 4 + 1;
                int column = index % 4 + 1;

                myData[index] += aMatrix(row, column);
            }

            return *this;
        }
        Matrix4x4<T>& operator-=(const Matrix4x4<T>& aMatrix)
        {
            for (int index = 0; index < 16; ++index)
            {
                int row = (index - (index % 4)) / 4 + 1;
                int column = index % 4 + 1;

                myData[index] -= aMatrix(row, column);
            }

            return *this;
        }
        void operator=(const Matrix4x4<T>& aMatrix)
        {
            for (int index = 0; index < 16; ++index)
            {
                int row = (index - (index % 4)) / 4 + 1;
                int column = index % 4 + 1;

                myData[index] = aMatrix(row, column);
            }
        }
        Matrix4x4<T> operator*(const Matrix4x4<T>& aMatrix)
        {
            Matrix4x4<T> matrix;
            
            matrix(1, 1) = myData[0] * aMatrix(1, 1) + myData[1] * aMatrix(2, 1) + myData[2] * aMatrix(3, 1) + myData[3] * aMatrix(4, 1);
            matrix(1, 2) = myData[0] * aMatrix(1, 2) + myData[1] * aMatrix(2, 2) + myData[2] * aMatrix(3, 2) + myData[3] * aMatrix(4, 2);
            matrix(1, 3) = myData[0] * aMatrix(1, 3) + myData[1] * aMatrix(2, 3) + myData[2] * aMatrix(3, 3) + myData[3] * aMatrix(4, 3);
            matrix(1, 4) = myData[0] * aMatrix(1, 4) + myData[1] * aMatrix(2, 4) + myData[2] * aMatrix(3, 4) + myData[3] * aMatrix(4, 4);
            
            matrix(2, 1) = myData[4] * aMatrix(1, 1) + myData[5] * aMatrix(2, 1) + myData[6] * aMatrix(3, 1) + myData[7] * aMatrix(4, 1);
            matrix(2, 2) = myData[4] * aMatrix(1, 2) + myData[5] * aMatrix(2, 2) + myData[6] * aMatrix(3, 2) + myData[7] * aMatrix(4, 2);
            matrix(2, 3) = myData[4] * aMatrix(1, 3) + myData[5] * aMatrix(2, 3) + myData[6] * aMatrix(3, 3) + myData[7] * aMatrix(4, 3);
            matrix(2, 4) = myData[4] * aMatrix(1, 4) + myData[5] * aMatrix(2, 4) + myData[6] * aMatrix(3, 4) + myData[7] * aMatrix(4, 4);
            
            matrix(3, 1) = myData[8] * aMatrix(1, 1) + myData[9] * aMatrix(2, 1) + myData[10] * aMatrix(3, 1) + myData[11] * aMatrix(4, 1);
            matrix(3, 2) = myData[8] * aMatrix(1, 2) + myData[9] * aMatrix(2, 2) + myData[10] * aMatrix(3, 2) + myData[11] * aMatrix(4, 2);
            matrix(3, 3) = myData[8] * aMatrix(1, 3) + myData[9] * aMatrix(2, 3) + myData[10] * aMatrix(3, 3) + myData[11] * aMatrix(4, 3);
            matrix(3, 4) = myData[8] * aMatrix(1, 4) + myData[9] * aMatrix(2, 4) + myData[10] * aMatrix(3, 4) + myData[11] * aMatrix(4, 4);
            
            matrix(4, 1) = myData[12] * aMatrix(1, 1) + myData[13] * aMatrix(2, 1) + myData[14] * aMatrix(3, 1) + myData[15] * aMatrix(4, 1);
            matrix(4, 2) = myData[12] * aMatrix(1, 2) + myData[13] * aMatrix(2, 2) + myData[14] * aMatrix(3, 2) + myData[15] * aMatrix(4, 2);
            matrix(4, 3) = myData[12] * aMatrix(1, 3) + myData[13] * aMatrix(2, 3) + myData[14] * aMatrix(3, 3) + myData[15] * aMatrix(4, 3);
            matrix(4, 4) = myData[12] * aMatrix(1, 4) + myData[13] * aMatrix(2, 4) + myData[14] * aMatrix(3, 4) + myData[15] * aMatrix(4, 4);

            return matrix;
        }
        Matrix4x4<T>& operator*=(const Matrix4x4<T>& aMatrix)
        {
            (*this) = (*this) * aMatrix;

            return *this;
        }

        static Matrix4x4<T> CreateRotationAroundX(T anAngleInRadians)
        {
            Matrix4x4<T> matrix;

            matrix(2, 2) = cos(anAngleInRadians);
            matrix(2, 3) = sin(anAngleInRadians);
            matrix(3, 2) = -matrix(2, 3);
            matrix(3, 3) = matrix(2, 2);

            return matrix;
        }
        static Matrix4x4<T> CreateRotationAroundY(T anAngleInRadians)
        {
            Matrix4x4<T> matrix;

            matrix(1, 1) = cos(anAngleInRadians);
            matrix(3, 1) = sin(anAngleInRadians);
            matrix(1, 3) = -matrix(3, 1);
            matrix(3, 3) = matrix(1, 1);

            return matrix;
        }
        static Matrix4x4<T> CreateRotationAroundZ(T anAngleInRadians)
        {
            Matrix4x4<T> matrix;

            matrix(1, 1) = cos(anAngleInRadians);
            matrix(1, 2) = sin(anAngleInRadians);
            matrix(2, 1) = -matrix(1, 2);
            matrix(2, 2) = matrix(1, 1);

            return matrix;
        }

        static Matrix4x4<T> Transpose(const Matrix4x4<T>& aMatrixToTranspose)
        {
            Matrix4x4<T> matrix;

            for (int index = 0; index < 16; ++index)
            {
                int row = (index - (index % 4)) / 4 + 1;
                int column = index % 4 + 1;

                matrix(row, column) = aMatrixToTranspose(column, row);
            }

            return matrix;
        }
    private:
        T myData[16];
    };
};

template <class T>
Utils::Vector4<T> operator*(const Utils::Vector4<T>& aVector, const Utils::Matrix4x4<T>& aMatrix)
{
    Utils::Vector4<T> vec;

    vec.x = CommonUtilities::Vector4<T>(aMatrix(1, 1), aMatrix(2, 1), aMatrix(3, 1), aMatrix(4, 1)).Dot(aVector);
    vec.y = CommonUtilities::Vector4<T>(aMatrix(1, 2), aMatrix(2, 2), aMatrix(3, 2), aMatrix(4, 2)).Dot(aVector);
    vec.z = CommonUtilities::Vector4<T>(aMatrix(1, 3), aMatrix(2, 3), aMatrix(3, 3), aMatrix(4, 3)).Dot(aVector);
    vec.w = CommonUtilities::Vector4<T>(aMatrix(1, 4), aMatrix(2, 4), aMatrix(3, 4), aMatrix(4, 4)).Dot(aVector);

    return vec;
}

template <class T>
const bool operator==(const Utils::Matrix4x4<T>& aMatrix, const Utils::Matrix4x4<T>& anotherMatrix)
{
    for (int index = 0; index < 16; ++index)
    {
        int row = (index - (index % 4)) / 4 + 1;
        int column = index % 4 + 1;

        if (aMatrix(row, column) != anotherMatrix(row, column))
        {
            return false;
        }
    }

    return true;
}

typedef Utils::Matrix4x4<float> m4f;
typedef Utils::Matrix4x4<double> m4d;
typedef Utils::Matrix4x4<int32_t> m4i;
typedef Utils::Matrix4x4<uint32_t> m4ui;