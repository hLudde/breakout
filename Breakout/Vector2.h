#pragma once

class Vector2 {
public:
	explicit Vector2(float x, float y): x(x), y(y) {
	}

	float x, y;

	Vector2 Normalize();
	Vector2 Negate();
	float Length() const;

protected:

private:
	
};