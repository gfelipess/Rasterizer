/*
										RASTERIZER BASE CLASS
						Control the Low-Level Functions related to the rasterizer project
*/

#ifndef _RASTERBASE_H_
#define _RASTERBASE_H_

// STL
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <memory>

// Windows WIN 32 API
#include <Windows.h>
#include <Wingdi.h>

// Color 
#include "Color.h"

using namespace std;

class RasterizerBase
{
	// Render Target
	RGB8Color* BackBuffer;
	RGB8Color* FrontBuffer;
	
	// 32 bit-precision Depth Buffer [0,1]
	double* DepthBuffer;

	// Stencil Buffer
	uint8_t* StencilBuffer;

	// Memory for the GDI API
	HBITMAP	   BufferBitmap;
	RGB8Color* GDIMemory;

	// Window Information
	uint16_t Width, Height;
	HWND hMainWindow;

protected:

	// Set Pixel on the Back Buffer
	void SetPixelRGB8(const uint16_t x, const uint16_t y, const RGB8Color color);

public:
	RasterizerBase();
	~RasterizerBase();

	
	void InitRasterizer(const uint16_t width, const uint16_t height, const HINSTANCE hisntance);

	// Clear Back Buffer
	void ClearBackBuffer(const RGB8Color color);
	void ClearDepthBuffer(const double value);

	// Swap Buffers
	void SwapBuffers();

	// Present Back Buffer
	void Present();

	// Windows Control Method
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif