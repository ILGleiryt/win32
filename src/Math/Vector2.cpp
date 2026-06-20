#include <math/Vectors/Vector2.h>

Vector2 operator+(Vector2 left, const Vector2& other)
{
	return left += other;
}

Vector2 operator-(Vector2 left, const Vector2& other)
{
	return left -= other;
}

Vector2 operator*(Vector2 left, const Vector2& other)
{
	return left *= other;
}

Vector2 operator*(Vector2 left, float scalar)
{
	return left *= scalar;
}

Vector2 operator*(float scalar, Vector2 right)
{
	return right *= scalar;
}

Vector2 operator/(Vector2 left, const Vector2& other)
{
	return left /= other;
}

std::ostream& operator<<(std::ostream& os, const Vector2& vec)
{
	os << "(" << vec.x << ", " << vec.y << ")";
	return os;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

bool Vector2::operator==(const Vector2& other) const
{
	return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other) const
{
	return !(*this == other);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2& other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2& other)
{
	x /= other.x;
	y /= other.y;
	return *this;
}