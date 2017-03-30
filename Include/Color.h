/*
									COLOR CLASS
*/

#ifndef COLOR_H_
#define COLOR_H_

#include <cstdint>

class RGB8Color
{

public:
	uint8_t r, g, b;

	// Constructor
	RGB8Color(uint8_t R = 0, uint8_t G = 0, uint8_t B = 0);
	RGB8Color(const RGB8Color& copy);

	// Destructor
	~RGB8Color();

	// Operators
	
};

// Some Default Colors
const RGB8Color WHITE_COLOR(255u, 255u, 255u);
const RGB8Color BLACK_COLOR(0u, 0u, 0u);
const RGB8Color RED_COLOR(255u, 0u, 0u);
const RGB8Color GREEN_COLOR(0u, 255u, 0u);
const RGB8Color BLUE_COLOR(0u, 0u, 255u);

#endif COLOR_H_