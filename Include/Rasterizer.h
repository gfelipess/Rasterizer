/*
								RASTERIZER INCLUDE COMPILATIONS
						Includes all the header files of the rasterizer project
*/
#ifndef _RASTERIZER_H_
#define _RASTERIZER_H_

#include "RasterizerBase.h"
#include "PolygonFilling.h"

class Rasterizer : public  RasterizerBase
{
	// Control Polygons ordering during rasterization 
	ActiveEdgeTable AET;

public:
	Rasterizer();
	~Rasterizer();

	void RasterizerPolygons();
};



#endif