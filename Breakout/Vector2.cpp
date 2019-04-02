#include "Vector2.h"
#include <complex>

float Vector2::Length() const {
	return std::sqrt(x * x + y * y);
}

Vector2 Vector2::Normalize() {
	const float len = Length();
	x = x / len;
	y = y / len;
	return *this;
}

Vector2 Vector2::Negate() {
	x = -x;
	y = -y;
	return *this;
}
