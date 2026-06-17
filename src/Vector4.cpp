#include <math/Vector4.h>

Vector4::Vector4() : x(0.f), y(0.f), z(0.f), w(0.f) {}

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{}

Vector4 operator+(Vector4 left, const Vector4& right)
{
    return left.add(right);
}

Vector4 operator-(Vector4 left, const Vector4& right)
{
    return left.substract(right);
}

Vector4 operator*(Vector4 left, const Vector4& right)
{
    return left.multiply(right);
}

Vector4 operator/(Vector4 left, const Vector4& right)
{
    return left.divide(right);
}

std::ostream& operator<<(std::ostream& os, const Vector4& vec)
{
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
    return os;
}


Vector4& Vector4::add(const Vector4& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;

    return *this;
}

Vector4& Vector4::substract(const Vector4& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;

    return *this;
}

Vector4& Vector4::multiply(const Vector4& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;

    return *this;
}

Vector4& Vector4::divide(const Vector4& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    w /= other.w;

    return *this;
}

bool Vector4::operator==(const Vector4& obj)
{
    return this->x == obj.x && this->y == obj.y 
        && this->z == obj.z && this->w == obj.z;
}

bool Vector4::operator!=(const Vector4& obj)
{
    return !(*this == obj);
}

Vector4& Vector4::operator+=(const Vector4& other)
{
    return add(other);
}

Vector4& Vector4::operator-=(const Vector4& other)
{
    return substract(other);
}

Vector4& Vector4::operator/=(const Vector4& other)
{
    return divide(other);
}

Vector4& Vector4::operator*=(const Vector4& other)
{
    return multiply(other);
}

Vector4 Vector4::Zero()
{
    return Vector4(0.f, 0.f, 0.f, 0.f);
}

Vector4 Vector4::One()
{
    return Vector4(1.f, 1.f, 1.f, 1.f);
}