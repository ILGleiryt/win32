#include <math/Vector3.h>

Vector3 operator+(Vector3 left, const Vector3& right)
{
    return left += right;
}

Vector3 operator-(Vector3 left, const Vector3& right)
{
    return left -= right;
}

Vector3 operator*(Vector3 left, const Vector3& right)
{
    return left *= right;
}

Vector3 operator/(Vector3 left, const Vector3& right)
{
    return left /= right;
}

std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

Vector3& Vector3::operator/=(const Vector3& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;

    return *this;
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator*=(const Vector3& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;

    return *this;
}

bool Vector3::operator==(const Vector3 & other) const
{
    return this->x == other.x && this->y == other.y && this->z == other.z;
}

bool Vector3::operator!=(const Vector3& other) const
{
    return !(*this == other);
}