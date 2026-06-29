#pragma once
#include <iostream>

struct Vector4
{
	float x, y, z, w;

	constexpr Vector4(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f) : x(x), y(y), z(z), w(w) {};

	friend Vector4 operator+(Vector4 left, const Vector4& right);
	friend Vector4 operator-(Vector4 left, const Vector4& right);
	friend Vector4 operator*(Vector4 left, const Vector4& right);
	friend Vector4 operator*(Vector4 left, const float scalar);
	friend Vector4 operator/(Vector4 left, const Vector4& right);

	bool operator==(const Vector4& obj);
	bool operator!=(const Vector4& obj);

	Vector4& operator+=(const Vector4& other);
	Vector4& operator-=(const Vector4& other);
	Vector4& operator*=(const Vector4& other);
	Vector4& operator/=(const Vector4& other);
	Vector4 operator-() const;

	static constexpr Vector4 Zero() { return Vector4(0.f, 0.f, 0.f, 0.f); }
	static constexpr Vector4 One()  { return Vector4(1.f, 1.f, 1.f, 1.f); }

	friend std::ostream& operator<<(std::ostream& os, const Vector4& vec);
};