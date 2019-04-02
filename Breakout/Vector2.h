#pragma once

class Vector2 {
public:
	explicit Vector2(): x(0), y(0) {}
	explicit Vector2(const float x, const float y): x(x), y(y) {
	}

	float x, y;

	Vector2 Normalize();
	Vector2 Negate();
	float Length() const;
};