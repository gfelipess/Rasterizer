#include "../Include/PolygonFilling.h"

//Polygon Class

Triangle::Triangle(Vector2 pos1, Vector2 pos2, Vector2 pos3, RGB8Color color)
{
	p1 = pos1;
	p2 = pos2;
	p3 = pos3;
	pColor = color;
}

Triangle::Triangle(const Triangle& polygon)
{
	p1 = polygon.p1;
	p2 = polygon.p2;
	p3 = polygon.p3;
	pColor = polygon.pColor;
}

Triangle::~Triangle(){ }


// Active Edge Table
ActiveEdgeTable::ActiveEdgeTable() { }
ActiveEdgeTable::~ActiveEdgeTable() { }

// Add Polygon to the Table
void ActiveEdgeTable::AddPolygon(Triangle polygon)
{
	

}

void ActiveEdgeTable::GetCurrentScanLine(uint16_t y)
{

}

void ActiveEdgeTable::CalculateIntersections()
{

}

void ActiveEdgeTable::DrawSpans()
{

}