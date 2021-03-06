// Final year project.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Final year project.h"
#include "Device .h"
#include "Input.h" 
#include "DPR RAY TRACER.h"
#include "CCamera.h"
#define MAX_LOADSTRING 100
// Global Variables:
HINSTANCE g_hInst = NULL;
HWND      g_hWnd = NULL;
HWND   Wind0w = NULL;
HDC fial = NULL;
const int ZERO = 0;
int Converter = 255;
int g_ViewportWidth = 1200; // rc.right - rc.left;
int g_ViewportHeight = 900; //rc.bottom - rc.top;
const  int area = g_ViewportHeight *g_ViewportWidth;
bool turnRight = false;
bool turnLeft = false;
bool Initwindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void Rendersnace(HDC* FinalOUTPUT, HWND* G_WMD);
int WINAPI wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//CDevice* Renderdevice = new CDevice;
	// Perform application initialization:
    if (!Initwindow(hInstance, nCmdShow))
    {
        return FALSE;
    }
	/*if (!Renderdevice->InitDevice(g_hWnd))
	{
		delete(Renderdevice);
	}*/
	//COLORREF red = (255, 0, 0);
	Wind0w = FindWindow(L"Final Year Project", L"DPR  Stage 3 ");
	fial = GetDC(Wind0w);
	Rendersnace(&fial,&Wind0w);
	MSG msg = { 0 };
    // Main message loop:
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else
		{
			//renderScance
			if (KeyHit(Key_Right))
			{
				turnRight = true;
				Rendersnace(&fial, &Wind0w);
				turnRight = false;
				KeyUpEvent(Key_Right);
			}
			
			if (KeyHit(Key_Left))
			{
				turnLeft = true;
				Rendersnace(&fial, &Wind0w);
				turnLeft = false;
				KeyUpEvent(Key_Left);
			}

			if (KeyHit(Key_Escape))
			{
				DestroyWindow(g_hWnd);
				KeyUpEvent(Key_Escape);

			}
		}
    }

    return (int) msg.wParam;
}

bool Initwindow(HINSTANCE hInstance, int nCmdShow)
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"Final Year Project";
	wcex.hIconSm = NULL;
	if (!RegisterClassEx(&wcex))
		return false;

	// Create window
	g_hInst = hInstance;
	RECT rc = { 0, 0, g_ViewportWidth, g_ViewportHeight};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hWnd = CreateWindow(L"Final Year Project", L"DPR  Stage 3 ", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL);
	if (!g_hWnd)
		return false;
	ShowWindow(g_hWnd, nCmdShow);

	return true;

}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		KeyDownEvent(static_cast<EKeyCode>(wParam));
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
void Rendersnace(HDC* FinalOUTPUT, HWND* G_WMD)
{
	std::vector<CModelTrangle> Triangles;
	std::vector<CModelSphere> Spheres;
	//std::vector<CLIGHTS> Lights;
	////CModelSphere(CVector3* Coord(postion), CVector3* Color(color of sphere),
	////float r(Raduis), CVector3* emissioncol(Color of suface), bool seethough(if it the sphere is see though), bool shiny(if it the sphere is shiny))
	Spheres.push_back(CModelSphere(&CVector3(0.0f, -10004.0f, -10.0f), &CVector3(0.2f, 0.2f, 0.4f), 10000.0f, &CVector3(0.0f, 0.0f, 0.0f),true,true));
	Spheres.push_back(CModelSphere(&CVector3(0.0, 0.5, -20), &CVector3(0.2f, 0.3f, 0.4f), 4.0, &CVector3(0.2f),false,true));
	Spheres[1].SetReftectionFactor(5.0f);
	Spheres.push_back(CModelSphere(&CVector3(10.0, 0.1, -15), &CVector3(0.2f, 0.3f, 0.44f), 3.0, &CVector3(0.3f),false,true));
	Spheres[2].SetReftectionFactor(10.0f);
	Spheres.push_back(CModelSphere(&CVector3(10.0, 0.2, -25), &CVector3(0.2f, 0.4f, 0.44f), 3.0, &CVector3(0.3f)));
	Spheres.push_back(CModelSphere(&CVector3(-10.0, 0.2, -15), &CVector3(0.2f, 0.6f, 0.44f), 3.0, &CVector3(0.3f),false,true));
	Spheres[4].SetReftectionFactor(10.0f);
	Spheres.push_back(CModelSphere(&CVector3(-10.0, 0.2, -25), &CVector3(0.2f, 0.8f, 0.44f), 3.0, &CVector3(0.3f)));
	/*Spheres.push_back(CModelSphere(&CVector3(13.0f, 0.3f, -35.0f), &CVector3(0.3f, 0.6f, 0.7f), 5.0f, &CVector3(0.0f, 0.0f, 0.0f),true));
	Spheres[1].SetTransparencyFactor(10.0f);
	Spheres.push_back(CModelSphere(&CVector3(-5.0f, 0.0f, -25.0f), &CVector3(0.1f, 0.2f, 0.3f), 1.5f, &CVector3(0.0f, 0.0f, 0.0f), true, true));
	Spheres[2].SetTransparencyFactor(10.0f);Spheres[2].SetReftectionFactor(5.5f);
	Spheres.push_back(CModelSphere(&CVector3(-15.0f, 0.3f, -35.0f), &CVector3(0.2f, 0.1f, 0.3f), 5.0f, &CVector3(0.0f, 0.0f, 0.0f), true, true));
	Spheres[3].SetTransparencyFactor(10.0f); Spheres[3].SetReftectionFactor(5.0f);
	Spheres.push_back(CModelSphere(&CVector3(-10.0f, 0.3f, -55.0f), &CVector3(0.1f, 0.2f, 0.3f), 5.0f, &CVector3(0.0f, 0.0f, 0.0f),  true, true));
	 Spheres[4].SetTransparencyFactor(10.0f);Spheres[4].SetReftectionFactor(5.0f);
	Spheres.push_back(CModelSphere(&CVector3(-3.0f, 0.3f, -65.0f), &CVector3(0.3f, 0.6f, 0.7f), 5.0f, &CVector3(0.0f, 0.0f, 0.0f),  true, true));
	Spheres[5].SetTransparencyFactor(10.5f);Spheres[5].SetReftectionFactor(5.0f);// 
	Spheres.push_back(CModelSphere(&CVector3(-10.0f, 0.3f, -75.0f), &CVector3(0.3f, 0.4f, 0.4f), 5.0f, &CVector3(0.0f, 0.0f, 0.0f), true, true));
	 Spheres[6].SetTransparencyFactor(10.5f);Spheres[6].SetReftectionFactor(5.0f);
	Spheres.push_back(CModelSphere(&CVector3(-3.0f, 0.3f, -70.0f), &CVector3(0.1f, 0.3f, 0.44f), 5.0f, &CVector3(0.0f, 0.0f, 0.0f), true, true));
	Spheres[7].SetTransparencyFactor(10.5f);Spheres[7].SetReftectionFactor(5.0f);
	Spheres.push_back(CModelSphere(&CVector3(5.0f, 0.2f, -45.0f), &CVector3(0.3f, 0.6f, 0.4f), 5.0f, &CVector3(0.0f, 0.0f, 0.0f), true));
	Spheres[8].SetTransparencyFactor(10.0f);// Spheres[9].SetTransparencyFactor(0.0f);
	Spheres.push_back(CModelSphere(&CVector3(0.0f, 0.1f, -35.0f), &CVector3(0.6f, 0.1f, 0.1f), 5.0f, &CVector3(0.0f, 0.0f, 0.0f), true));
	Spheres[9].SetTransparencyFactor(10.0f);*/// Spheres[3].SetTransparencyFactor(0.5f);
	//////CVector3* position, CVector3* Direction, CVector3* Color, bool turnOn = false (used for turning the light on and off)
	//////bool Effects = false(other effects that may look cool). 
	Spheres.push_back(CModelSphere(&CVector3(0.0f, 20.0f, -50.0f), &CVector3(0.0f, 0.0f, 0.0f), 0.5f, &CVector3(2)));
	/// CModelTrangle(CVector3 &p1, CVector3 &p2, CVector3 &p3, CVector3 &Color, float number);
	//Triangles.push_back(CModelTrangle(CVector3(-10.0f, -10.0f, -50.0f), CVector3(10.0f, -10.0f, -50.0), CVector3(0.0f, 10.0f, -50.0f), 
	///CVector3(0.0f, 8.0f, 0.0), 1));
	//Triangles.push_back(CModelTrangle(CVector3(-10.0f, -10.0f, -50.0f), CVector3(10.0f, -10.0f, -50.0), CVector3(0.0f, 10.0f, -50.0f), 
	//CVector3(0.0f, 8.0f, 0.0), 1));
	////a smart pointer used for the 
	auto FinalCOLor = std::make_unique<CVector3>(0, 0, 0); //// the final color for the pixel 
	CVector3 *image = new CVector3[area], *pixel = image;//// the holder for the final pixel color and  location  
	auto MainCamera = std::make_unique<CCamera>(g_ViewportHeight, g_ViewportWidth, 51.52f);
	for (int i = 0; i < area; ++i)
	{
		image[i].X = 1;
		image[i].Y = 1;
		image[i].Z = 1;
	}
	//MainCamera->SEtOrgin(&CVector3(0, 0, 0)); //// the orgin of the what will become part of the camera class.

	auto P_Ray = std::make_unique<CRay_IN>();//// makes the class used to render the objects.
	CVector3 orgin = CVector3(0,6, 10);
	//orgin.setX(;
	int h = 1;
	if (turnRight)
	{
		orgin.setX(sin(h));
		/*void RotateLocalY(const TFloat32 y)
		{
			// Need to adjust for scaling component of matrix - matrix assumed to be Scale*Rot*Trans,
			// becoming Scale*[YRot*Rot]*Trans
			TFloat32 scaleSqX = e00 * e00 + e01 * e01 + e02 * e02;
			TFloat32 scaleSqZ = e20 * e20 + e21 * e21 + e22 * e22;
			GEN_ASSERT_OPT(!IsZero(scaleSqX) && !IsZero(scaleSqZ), "Singular matrix");
			TFloat32 scaleZX = Sqrt(scaleSqZ) * InvSqrt(scaleSqX);

			TFloat32 sY, cY, sYZ, sYX;
			SinCos(y, &sY, &cY);
			sYZ = sY * scaleZX;
			sYX = sY / scaleZX;

			// Perform minimum of calculations rather than use full matrix multiply
			TFloat32 t;
			t = e20 * cY + e00 * sYZ;
			e00 = e00 * cY - e20 * sYX;
			e20 = t;
			t = e21 * cY + e01 * sYZ;
			e01 = e01 * cY - e21 * sYX;
			e21 = t;
			t = e22 * cY + e02 * sYZ;
			e02 = e02 * cY - e22 * sYX;
			e22 = t;
		}*/
		h+10;
	}
	if (turnLeft)
	{
		orgin.setX(-h);
		h-10;
	}
	float inW = 1 / float(g_ViewportWidth);
	float inH = 1 / float(g_ViewportHeight);
	//// The Pixel for loop used to the ray. 
	for (int y = 0; y < g_ViewportHeight; y++)
	{
		for (int x = 0; x < g_ViewportWidth ; x++, ++pixel)
		{
			float xx = (2 * (x + 0.5)  *  inW - 1.0) *MainCamera->GETangle() * MainCamera->GETaspectratio();// *   //GETscale();
			float yy = (1 - 2 * (y + 0.5) *  inH)*  MainCamera->GETangle();// GETscale();


			CVector3 raydir(xx, yy, -1);
			raydir.NormaliZe();
			*pixel = P_Ray->RunTrace(orgin, raydir, Spheres, Triangles, 0);//// works out and returns the final color of the pixel.
			// = //*FinalCOLor;
			// This returns the color  for the pixel. 
		}
	}
	//// kills but a smart pointer used  the  rander  class.

	std::ofstream ofs("./RanderedImage.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << g_ViewportWidth << " " << g_ViewportHeight << "\n255\n";
	for (int i = 0; i < area; ++i)
	{
		ofs << (unsigned char)(fmin(float(1), image[i].GetX()) * 255) <<
			(unsigned char)(fmin(float(1), image[i].GetY()) * 255) <<
			(unsigned char)(fmin(float(1), image[i].GetZ()) * 255);
	}
	ofs.close();
	COLORREF H;
	int i = 0;
	for (int y = 0; y < g_ViewportHeight; y++)
	{
		for (int x = 0; x < g_ViewportWidth; x++, ++i)
		{
			H = RGB((fmin(float(1), image[i].GetX()) * 255),
				(fmin(float(1), image[i].GetY()) * 255),
				(fmin(float(1), image[i].GetZ()) * 255));
			SetPixel(*FinalOUTPUT, x, y, H);
		}
	}
	if (FinalCOLor) FinalCOLor.release();
	if (P_Ray) P_Ray.release();
	if (MainCamera) MainCamera.release();
	if (!Triangles.empty()) Triangles.empty();
	if (!Spheres.empty())  Spheres.erase(Spheres.begin(), Spheres.end());/// .empty();
	//if (pixel) delete(&pixel);
	//if (image) delete[] image;
}