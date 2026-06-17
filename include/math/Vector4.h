#pragma once
#include <iostream>

struct Vector4
{
	float x, y, z, w;
	Vector4();
	Vector4(float x, float y, float z, float w);

	Vector4& add(const Vector4& other);
	Vector4& substract(const Vector4& other);
	Vector4& multiply(const Vector4& other);
	Vector4& divide(const Vector4& other);

	friend Vector4 operator+(Vector4 left, const Vector4& right);
	friend Vector4 operator-(Vector4 left, const Vector4& right);
	friend Vector4 operator*(Vector4 left, const Vector4& right);
	friend Vector4 operator/(Vector4 left, const Vector4& right);

	bool operator==(const Vector4& obj);
	bool operator!=(const Vector4& obj);

	Vector4& operator+=(const Vector4& other);
	Vector4& operator-=(const Vector4& other);
	Vector4& operator*=(const Vector4& other);
	Vector4& operator/=(const Vector4& other);

	Vector4 Zero();
	Vector4 One();

	friend std::ostream& operator<<(std::ostream& os, const Vector4& vec);
};