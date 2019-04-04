#pragma once

class Vector2 {
public:
	explicit Vector2(): x(0), y(0) {}
	explicit Vector2(const float x, const float y): x(x), y(y) {}

	float x, y;

	Vector2 Normalize() const;
	Vector2 Negate() const;
	float Length() const;

	Vector2 operator+ (Vector2 other) const;
	Vector2 operator- (Vector2 other) const;
	Vector2 operator* (float scalar) const;
	Vector2 operator/ (float divisor) const;
};