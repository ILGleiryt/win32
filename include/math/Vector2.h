#pragma once
#include <iostream>

struct Vector2
{
	float x, y;
	Vector2();
	Vector2(float x, float y);

	Vector2& add(const Vector2& other);
	Vector2& substract(const Vector2& other);
	Vector2& multiply(const Vector2& other);
	Vector2& divide(const Vector2& other);

	friend Vector2 operator+(Vector2 left,const Vector2& right);
	friend Vector2 operator-(Vector2 left, const Vector2& right);
	friend Vector2 operator*(Vector2 left, const Vector2& right);
	friend Vector2 operator/(Vector2 left, const Vector2& right);

	bool operator==(const Vector2& obj);
	bool operator!=(const Vector2& obj);

	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*=(const Vector2& other);
	Vector2& operator/=(const Vector2& other);

	Vector2 Zero();
	Vector2 One();

	friend std::ostream& operator<<(std::ostream& os, const Vector2& vec);
};
