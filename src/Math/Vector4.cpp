#include <math/Vectors/Vector4.h>

Vector4 operator+(Vector4 left, const Vector4& right)
{
    return left += right;
}

Vector4 operator-(Vector4 left, const Vector4& right)
{
    return left -= right;
}

Vector4 operator*(Vector4 left, const Vector4& right)
{
    return left *= right;
}

Vector4 operator*(Vector4 left, const float scalar)
{
    return left *= scalar;
}

Vector4 operator/(Vector4 left, const Vector4& right)
{
    return left /= right;
}

std::ostream& operator<<(std::ostream& os, const Vector4& vec)
{
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    return os;
}

bool Vector4::operator==(const Vector4& other)
{
    return this->x == other.x && this->y == other.y
        && this->z == other.z && this->w == other.z;
}

bool Vector4::operator!=(const Vector4& other)
{
    return !(*this == other);
}

Vector4& Vector4::operator+=(const Vector4& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;

    return *this;
}

Vector4& Vector4::operator-=(const Vector4& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;

    return *this;
}

Vector4& Vector4::operator/=(const Vector4& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    w /= other.w;

    return *this;
}

Vector4 Vector4::operator-() const
{
    return Vector4(-x, -y, -z, -w);
}

Vector4& Vector4::operator*=(const Vector4& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;

    return *this;
}