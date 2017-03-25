#include "../Include/Color.h"

// Constructors
RGB8Color::RGB8Color(uint8_t R, uint8_t G, uint8_t B)
{
	RGB8Color::r = R;
	RGB8Color::g = G;
	RGB8Color::b = B;
}
RGB8Color::RGB8Color(const RGB8Color& copy)
{
	RGB8Color::r = copy.r;
	RGB8Color::g = copy.g;
	RGB8Color::b = copy.b;
}

// Destructor
RGB8Color::~RGB8Color() {}


