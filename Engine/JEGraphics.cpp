#include "JEGraphics.h"

//==============================================
//			CONSTRUCTORS & DESTRUCTOR
//==============================================

//==============================================
JEGraphics::JEGraphics()
{
	m_pD3D = 0;
}


//==============================================
JEGraphics::JEGraphics(
	const JEGraphics& other
)
{
}


//==============================================
JEGraphics::~JEGraphics()
{
}


//==============================================
//				   METHODS
//==============================================

//==============================================
bool JEGraphics::Initialize(
	int screenWidth, 
	int screenHeight, 
	HWND hwnd
)
{
	bool result;

	//==============================================
	// Utworzenie i inicjalizacja obiektu Direct3D
	m_pD3D = new JED3D;

	if (!m_pD3D)
	{
		return false;
	}

	result = m_pD3D->Initialize(
		screenWidth,
		screenHeight,
		VSYNC_ENABLED,
		hwnd,
		FULL_SCREEN,
		SCREEN_DEPTH,
		SCREEN_NEAR
	);

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);

		return false;
	}
	//==============================================

	return true;
}


//==============================================
void JEGraphics::Shutdown()
{
	if (m_pD3D)
	{
		m_pD3D->Shutdown();
		delete m_pD3D;
		m_pD3D = 0;
	}
}


//==============================================
bool JEGraphics::Frame()
{
	bool result;
	
	result = Render();

	return result;
}


//==============================================
bool JEGraphics::Render()
{
	m_pD3D->BeginScene(
		0.5f,
		0.5f,
		0.5f,
		1.f
	);

	m_pD3D->EndScene();

	return true;
}