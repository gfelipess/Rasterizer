#ifndef _MATHEMATICS_H_
#define _MATHEMATICS_H_

#include <cmath>

class Vector2
{
public: 
	double x_pos, y_pos;

	Vector2(double x = 0.0, double y = 0.0);
	Vector2(const Vector2& vec);
	~Vector2();

	// Basic Operations
	Vector2 operator + (Vector2& vec);
	Vector2 operator - (Vector2& vec);
};


#endif