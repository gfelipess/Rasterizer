#include "..\Include\RasterizerBase.h"

RasterizerBase::RasterizerBase() {}
RasterizerBase::~RasterizerBase() 
{
	if (BackBuffer)
		delete[] BackBuffer;
	if (FrontBuffer)
		delete[] FrontBuffer;
	if (DepthBuffer)
		delete[] DepthBuffer;

	// Delete Bitmap Buffer
	DeleteObject(BufferBitmap);
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

	// Get Window Device Context
	const HDC hdc = GetDC(hMainWindow);

	// Allocate Back Buffer
	BackBuffer  = new RGB8Color[Width*Height];

	// Allocate Front Buffer
	FrontBuffer = new RGB8Color[Width*Height];

	// Allocate Depth Buffer
	DepthBuffer = new double[Width*Height];

	// Initialize the Memory that the GDI library will receive
	BITMAPINFO bitmap;
	ZeroMemory(&bitmap, sizeof(bitmap));

	bitmap.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmap.bmiHeader.biWidth = Width;
	bitmap.bmiHeader.biHeight = Height;
	bitmap.bmiHeader.biPlanes = 1;
	bitmap.bmiHeader.biBitCount = 24;
	bitmap.bmiHeader.biCompression = BI_RGB;

	// Create the Handle to the Device Independent Bitmap
	BufferBitmap = CreateDIBSection(hdc, &bitmap, DIB_RGB_COLORS, (void**)&GDIMemory, NULL, 0);
}


/*
										Low-Level Methods
*/

//Per-Pixel Methods
void RasterizerBase::SetPixelRGB8(const uint16_t x, const uint16_t y, const RGB8Color color)
{
	// Change endianness
	// GDI uses BGR not RGB
	RGB8Color color_gdi;
	color_gdi.r = color.b;
	color_gdi.g = color.g;
	color_gdi.b = color.r;

	BackBuffer[Width*y + x] = color_gdi;
}

// Clear Methods
void RasterizerBase::ClearBackBuffer(const RGB8Color color)
{
	// Clear Back Buffer 
	for (uint16_t y = 0; y < Height; ++y)
		for (uint16_t x = 0; x < Width; ++x)
			SetPixelRGB8(x, y, color);
}

void RasterizerBase::ClearDepthBuffer(const double value)
{
	// Clear Depth Buffer 
	for (uint16_t y = 0; y < Height; ++y)
		for (uint16_t x = 0; x < Width; ++x)
			DepthBuffer[Width*y + x] = value;
}

// Swap and Presentation
void RasterizerBase::SwapBuffers()
{
	// Swap Back and Front Buffer
	std::swap(BackBuffer, FrontBuffer);

	// Fill the GDI memory
	memcpy((void*)GDIMemory, (void*)FrontBuffer, Width*Height*sizeof(RGB8Color));
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

	// Handle the Bitmap
	const HDC hdcmem = CreateCompatibleDC(hdc);

	// Pass the bitmap information to the memory handle
	SelectObject(hdcmem, BufferBitmap);

	// Copy from the Front Buffer to the Window
	BitBlt(hdc, 0, 0, Width, Height, hdcmem, 0, 0, SRCCOPY);

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