#ifndef _POLYGON_FILLING_H_
#define _POLYGON_FILLING_H_

#include <map>

#include "RasterizerBase.h"
#include "Mathematics.h"

// Define Polygon Class
class Triangle
{
protected:
	// position information
	Vector2 p1, p2, p3;

	// Solid Color 
	RGB8Color pColor;

public:
	Triangle() {}
	Triangle(Vector2 pos1, Vector2 pos2, Vector2 pos3, RGB8Color color);
	Triangle(const Triangle& polygon);
	~Triangle();
};

// Store the Polygons edges sorted by y coordinate using bucket sort
// in Active Edge Table

class ActiveEdgeTable : protected Triangle
{
	// Represent Edges
	struct EdgeInformation
	{
		// Information about the edge geometry
		double
			xmin, ymin, xmax, ymax,
			slope;

		// Information about the polygon this edge is part of
		Triangle* polygon;

		EdgeInformation(double ymin, double ymax, double xmin, double xmax)
		{
			// Fill edge information
			EdgeInformation::ymin = ymin;
			EdgeInformation::ymax = ymax;
			EdgeInformation::xmin = xmin;
			EdgeInformation::xmax = xmax;
			slope = (ymax - ymin) / (xmax - xmin);
		}
		~EdgeInformation() { polygon = nullptr; }
	};


	// Store the edges 
	std::vector<EdgeInformation> Edges;

	// Store the current edges on the table being rasterized
	std::vector<EdgeInformation> CurrentEdges;

	//TODO: IS NECESSARY TO IMPLEMENT A CUSTOM SORT FOR THE type EdgeInformation 
	//TODO: based on the xmin position. The algorithm can't continue without it
	// http://fusharblog.com/3-ways-to-define-comparison-functions-in-cpp/

public:
	ActiveEdgeTable();
	~ActiveEdgeTable();

	// Get the current scan line for check the edges which are intersected
	// and delete the ones not needed anymore
	void GetCurrentScanLine(uint16_t y);

	// Calculate Intersections with the current scan-line
	void CalculateIntersections();

	// Draw the spans
	void DrawSpans();

	// Add polygon to the AET
	void AddPolygon(Triangle polygon);
};


#endif


