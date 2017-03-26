#include "..\Include\RasterizerBase.h"

//TODO: - 1 Continue the implementation the best fast pixel copy operation using BitBlit

RasterizerBase::RasterizerBase() {}
RasterizerBase::~RasterizerBase() 
{
	if (BackBuffer)
		delete[] BackBuffer;
	if (FrontBuffer)
		delete[] FrontBuffer;
	if (DepthBuffer)
		delete[] DepthBuffer;
}

/* 
											Methods
*/
void RasterizerBase::InitRasterizer(const uint16_t width, const uint16_t height,
	const HINSTANCE hisntance)
{
	/*
		Initialize Windows
	*/
	
	// Create the Window Class
	WNDCLASSEX WindowClass = {};
	WindowClass.lpszClassName = "BasicWindowClass";
	WindowClass.cbSize = sizeof(WNDCLASSEX);
	WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	WindowClass.hInstance = hisntance;
	WindowClass.lpfnWndProc = WindowProc;

	if (RegisterClassEx(&WindowClass) == 0)
		MessageBox(NULL, "Wasn't Possible register the Class", "ERROR", MB_OK | MB_ICONERROR);

	// Create the Window
	hMainWindow = CreateWindowEx(0, WindowClass.lpszClassName, "Rasterizer Project",  
		WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 
		NULL, NULL, hisntance, nullptr);

	// Check if the Windows was created
	if (hMainWindow == NULL)
		MessageBox(NULL, "Wasn't Possible create the Window", "ERROR", MB_OK | MB_ICONERROR);

	// Get the dimensions of the Back Buffer
	RECT rc;
	GetClientRect(hMainWindow, &rc);

	Width = (uint16_t)rc.right;
	Height = (uint16_t)rc.bottom;

	// Allocate Back Buffer
	BackBuffer  = new RGB8Color[Width*Height];

	// Allocate Front Buffer
	FrontBuffer = new RGB8Color[Width*Height];

	// Allocate Depth Buffer
	DepthBuffer = new double[Width*Height];
}


/*
										Low-Level Methods
*/

// SetPixlRGB8 method
//! This must be the method utilized to access pixels the pixels 
void RasterizerBase::SetPixelRGB8(const uint16_t x, const uint16_t y, const RGB8Color color)
{
	BackBuffer[Height*y + x] = color;
}

void RasterizerBase::ClearBackBuffer(RGB8Color color)
{
	// Clear Back Buffer and Depth Buffer
	for (uint16_t y = 0; y < Height; ++y)
		for (uint16_t x = 0; x < Width; ++x)
		{
			BackBuffer[y*Height + x] = color;
			// Clear to the max value so any new value 
			// get updated for the pixel
			DepthBuffer[y*Height + x] = 1.0;
		}
}

void RasterizerBase::SwapBuffers()
{
	// Swap Back and Front Buffer
	RGB8Color* const tmp = BackBuffer;
	BackBuffer = FrontBuffer;
	FrontBuffer = tmp;
}

void RasterizerBase::Present()
{
	// GDI Control 
	PAINTSTRUCT ps; 

	// Begin Drawing on the window
	const HDC hdc = BeginPaint(hMainWindow, &ps);

	/*
			Copy Pixels from the Front Buffer to the Window
	*/

	// Bitmap to represent the back buffer for using the GDI functions
	HBITMAP bitmap;

	// Create an Memory device context compatible with the device context
	HDC hMDC = CreateCompatibleDC(hdc);
	bitmap = CreateCompatibleBitmap(hdc, Width, Height);

	// Use an colored bitmap
	SelectObject(hMDC, bitmap);

	// Describe the Bitmap
	BITMAPINFO bitmapInfo;

	// Copy Pixes from the Front Buffer to the GDI interface
	SetDIBits(hdc, bitmap, 0, Height, (void*)FrontBuffer, &bitmapInfo, 0);

	DeleteObject(bitmap);
	// End drawing on the window
	EndPaint(hMainWindow, &ps);
}


// Control Windows Messages
LRESULT CALLBACK RasterizerBase::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CLOSE)
		PostQuitMessage(0);
	else if (wParam == VK_ESCAPE)
		PostQuitMessage(0);
	
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}