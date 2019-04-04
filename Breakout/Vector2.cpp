#include "Vector2.h"
#include <complex>

float Vector2::Length() const {
	return std::sqrt(x * x + y * y);
}

Vector2 Vector2::operator+(const Vector2 other) const
{
	Vector2 result;

	result.x = x + other.x;
	result.y = y + other.y;

	return result;
}

Vector2 Vector2::operator-(const Vector2 other) const
{
	Vector2 result;

	result.x = x - other.x;
	result.y = y - other.y;

	return result;
}

Vector2 Vector2::operator*(const float scalar) const
{
	Vector2 result;

	result.x = x * scalar;
	result.y = y * scalar;

	return result;
}

Vector2 Vector2::operator/(const float divisor) const
{
	Vector2 result;

	result.x = x / divisor;
	result.y = y / divisor;

	return result;
}

Vector2 Vector2::Normalize() const
{
	return *this / Length();
}

Vector2 Vector2::Negate() const
{
	return *this * -1;

}
