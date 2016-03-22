#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <cmath>

class Vector3
{
    public:
        float x, y, z;

    public:
        Vector3(float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
        {
            this->x = X;
            this->y = Y;
            this->z = Z;
        }

        Vector3 operator+=(const Vector3 &vec)
        {
            return (*this = (*this + vec));
        }

        Vector3 operator+(const Vector3 &vec)
        {
            return Vector3(vec.x + this->x, vec.y + this->y, vec.z + this->z);
        }

        Vector3 operator-=(const Vector3 &vec)
        {
            return (*this = (*this - vec));
        }

        Vector3 operator-(const Vector3 &vec)
        {
            return Vector3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
        }

        Vector3 operator*=(float num)
        {
            return (*this = (*this * num));
        }

        Vector3 operator*(float num)
        {
            return Vector3(this->x * num, this->y * num, this->z * num);
        }

        Vector3 operator/=(float num)
        {
            return (*this = (*this / num));
        }

        Vector3 operator/(float num)
        {
            return Vector3(this->x / num, this->y / num, this->z / num);
        }

        Vector3 operator-()
        {
            return Vector3(-this->x, -this->y, -this->z);
        }

        bool operator==(Vector3 &vec)
        {
            return ((vec.x == this->x) && (vec.y == this->y) && (vec.z == this->z));
        }

        bool operator!=(Vector3 &vec)
        {
            return !(vec == *this);
        }

        Vector3 operator*(const Vector3 &vec)
        {
            return Vector3((this->y * vec.z - this->z * vec.y),
                           (this->z * vec.x - this->x * vec.z),
                           (this->x * vec.y - this->y * vec.x));
        }

        float Dot(Vector3 &vec)
        {
            return (this->x * vec.x + this->y * vec.y + this->z * vec.z);
        }

        float Length()
        {
            return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
        }

        Vector3 Normalize()
        {
            float length = this->Length();

            this->x /= length;
            this->y /= length;
            this->z /= length;

            return *this;
        }

        float Distance(Vector3 &vec)
        {
            float disX = vec.x - this->x;
            float disY = vec.y - this->y;
            float disZ = vec.z - this->z;

            return sqrt(pow(disX, 2) + pow(disY, 2) + pow(disZ, 2));
        }

        friend std::ostream& operator<<(std::ostream &strm, const Vector3 &vec)
        {
            return (strm << vec.x << '\t' << vec.y << '\t' << vec.z);
        }
};

#endif // VECTOR3_H
