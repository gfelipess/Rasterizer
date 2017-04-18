#include "../Include/Rasterizer.h"

Rasterizer::Rasterizer() {}
Rasterizer::~Rasterizer() {}

// Rasterizer the Polygons on the Clipped Screen
void Rasterizer::RasterizerPolygons() 
{
	// Polygon Filling Algorithm
	/*
					Passes 
			1.  Find all intersection with the current y[i] scan line
			2.  Sort the intersection by the x coordinate
			3.  Draw the spans with odd-parity	
	*/

	// Rasterizer the polygons in the screen
	for (uint16_t y = 0; y < Height; ++y){

		// Check if new edges enter with this scan line and exclude the ones with y = ymax
		AET.GetCurrentScanLine(y);

		// Check intersection with the current scan line
		AET.CalculateIntersections();

		// Draw the spans
		AET.DrawSpans();
	}

}