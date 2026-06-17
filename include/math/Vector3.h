#pragma once
#include <iostream>

struct Vector3
{
	float x, y, z;
	Vector3();
	Vector3(float x, float y, float z);

	Vector3& add(const Vector3& other);
	Vector3& substract(const Vector3& other);
	Vector3& multiply(const Vector3& other);
	Vector3& divide(const Vector3& other);

	friend Vector3 operator+(Vector3 left, const Vector3& right);
	friend Vector3 operator-(Vector3 left, const Vector3& right);
	friend Vector3 operator*(Vector3 left, const Vector3& right);
	friend Vector3 operator/(Vector3 left, const Vector3& right);

	bool operator==(const Vector3& obj);
	bool operator!=(const Vector3& obj);

	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(const Vector3& other);
	Vector3& operator/=(const Vector3& other);

	Vector3 Zero();
	Vector3 One();

	friend std::ostream& operator<<(std::ostream& os, const Vector3& vec);
};