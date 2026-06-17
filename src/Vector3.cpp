#include <math/Vector3.h>

Vector3 operator+(Vector3 left, const Vector3& right)
{
    return left.add(right);
}

Vector3 operator-(Vector3 left, const Vector3& right)
{
    return left.substract(right);
}

Vector3 operator*(Vector3 left, const Vector3& right)
{
    return left.multiply(right);
}

Vector3 operator/(Vector3 left, const Vector3& right)
{
    return left.divide(right);
}

std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

Vector3::Vector3() : x(0.f), y(0.f), z(0.f) {}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{}

Vector3& Vector3::add(const Vector3 & other)
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Vector3& Vector3::substract(const Vector3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

Vector3& Vector3::multiply(const Vector3& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;

    return *this;
}

Vector3& Vector3::divide(const Vector3& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;

    return *this;
}

bool Vector3::operator==(const Vector3& obj)
{
    return this->x == obj.x && this->y == obj.y && this->z == obj.z;
}

bool Vector3::operator!=(const Vector3& obj)
{
    return !(*this == obj);
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    return add(other);
}

Vector3& Vector3::operator-=(const Vector3& other)
{
    return substract(other);
}

Vector3& Vector3::operator/=(const Vector3& other)
{
    return divide(other);
}

Vector3& Vector3::operator*=(const Vector3& other)
{
    return multiply(other);
}

Vector3 Vector3::Zero()
{
    return Vector3(0.f, 0.f, 0.f);
}

Vector3 Vector3::One()
{
    return Vector3(1.f, 1.f, 1.f);
}