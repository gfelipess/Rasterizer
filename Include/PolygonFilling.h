#ifndef _POLYGON_FILLING_H_
#define _POLYGON_FILLING_H_

#include "RasterizerBase.h"
#include "Mathematics.h"

// Define Polygon Class
class Triangle
{
	// position information
	Vector2 p1, p2, p3;

	// Solid Color 
	RGB8Color pColor;

public:
	Triangle(Vector2 pos1, Vector2 pos2, Vector2 pos3, RGB8Color color);
	Triangle(const Triangle& polygon);
	~Triangle();
};

// Store the Polygons edges sorted by y coordinate using bucket sort
// in Active Edge Table

class ActiveEdgeTable
{

public:
	ActiveEdgeTable();
	~ActiveEdgeTable();

	// Add polygon to the AET
	void AddPolygon(Triangle polygon);
	void DeletePolygon(Triangle polygon);
	void ClearEdge();
};


#endif


