#pragma once
#include <iostream>

struct Vector3
{
	float x, y, z;

	constexpr Vector3(float x = 0.f, float y = 0.f, float z = 0.f) : x(x), y(y), z(z) {}

	friend Vector3 operator+(Vector3 left, const Vector3& right);
	friend Vector3 operator-(Vector3 left, const Vector3& right);
	friend Vector3 operator*(Vector3 left, const Vector3& right);
	friend Vector3 operator/(Vector3 left, const Vector3& right);

	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;

	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(const Vector3& other);
	Vector3& operator/=(const Vector3& other);
	Vector3 operator-() const;


	static constexpr Vector3 Zero() { return Vector3(0.f, 0.f, 0.f); }
	static constexpr Vector3 One()  { return Vector3(1.f, 1.f, 1.f); }

	friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);
};