#pragma once
#include <iostream>

struct Vector2
{
	float x, y;

	constexpr Vector2(float x = 0.f, float y = 0.f) : x(x), y(y) {}

	friend Vector2 operator+(Vector2 left,const Vector2& other);
	friend Vector2 operator-(Vector2 left, const Vector2& other);
	friend Vector2 operator*(Vector2 left, const Vector2& other); //vec2 * vec2
	friend Vector2 operator*(Vector2 left, float scalar); //vec2 * scalar
	friend Vector2 operator*(float scalar, Vector2 right);
	friend Vector2 operator/(Vector2 left, const Vector2& other);
	Vector2 operator-() const;

	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;

	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*=(const Vector2& other);
	Vector2& operator/=(const Vector2& other);
	
	static constexpr Vector2 Zero() { return Vector2(0.f, 0.f); }
	static constexpr Vector2 One()  { return Vector2(1.f, 1.f); }

	friend std::ostream& operator<<(std::ostream& os, const Vector2& vec);
};
