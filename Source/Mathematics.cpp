#include "../Include/Mathematics.h"

Vector2::Vector2(double x, double y)
{
	x_pos = x;
	y_pos = y;
}

Vector2::Vector2(const Vector2& vec)
{
	x_pos = vec.x_pos;
	y_pos = vec.y_pos;
}

Vector2::~Vector2(){}

// Basic Operations

