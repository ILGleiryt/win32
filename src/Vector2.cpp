#include <math/Vector2.h>

Vector2::Vector2() : x(0.f), y(0.f) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 operator+(Vector2 left, const Vector2& right)
{
	return left.add(right);
}

Vector2 operator-(Vector2 left, const Vector2& other)
{
	return left.substract(other);
}

Vector2 operator*(Vector2 left, const Vector2& other)
{
	return left.multiply(other);
}

Vector2 operator/(Vector2 left, const Vector2& other)
{
	return left.divide(other);
}

std::ostream& operator<<(std::ostream& os, const Vector2& vec)
{
	os << "(" << vec.x << ", " << vec.y << ")";
	return os;
}


Vector2& Vector2::add(const Vector2 & other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2& Vector2::substract(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2& Vector2::multiply(const Vector2& other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

Vector2& Vector2::divide(const Vector2& other)
{
	x /= other.x;
	y /= other.y;
	return *this;
}

bool Vector2::operator==(const Vector2& obj)
{
	return x == obj.x && y == obj.y;
}

bool Vector2::operator!=(const Vector2& obj)
{
	return !(*this == obj);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	return add(other);
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	return substract(other);
}

Vector2& Vector2::operator*=(const Vector2& other)
{
	return multiply(other);
}

Vector2& Vector2::operator/=(const Vector2& other)
{
	return divide(other);
}

Vector2 Vector2::Zero() { return Vector2(0.f, 0.f); }

Vector2 Vector2::One() { return Vector2(1.f, 1.f); }
