#include "JEGraphics.h"

//==============================================
//			CONSTRUCTORS & DESTRUCTOR
//==============================================

//==============================================
JEGraphics::JEGraphics()
{
	m_pD3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_TextureShader = 0;
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

	// Create the camera object.
	m_Camera = new JECamera;

	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(
		0.0f, 
		0.0f, 
		-5.0f);

	// Create the model object.
	m_Model = new JEModel;

	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(
		m_pD3D->GetDevice(),
		L"../Engine/data/seafloor.dds");

	if (!result)
	{
		MessageBox(
			hwnd, 
			L"Could not initialize the model object.", 
			L"Error", 
			MB_OK);

		return false;
	}

	// Create the color shader object.
	m_TextureShader = new JETextureShader;

	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_TextureShader->Initialize(
		m_pD3D->GetDevice(), 
		hwnd);
	
	if (!result)
	{
		MessageBox(
			hwnd, 
			L"Could not initialize the color shader object.",
			L"Error", 
			MB_OK);

		return false;
	}

	return true;
}


//==============================================
void JEGraphics::Shutdown()
{
	// Release the color shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

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
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_pD3D->BeginScene(
		0.0f, 
		0.0f, 
		0.0f, 
		1.0f);

	// Generate the view matrix based on the 
	// camera's position.
	m_Camera->Render();

	// Get the world, view, and projection 
	// matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_pD3D->GetWorldMatrix(worldMatrix);
	m_pD3D->GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on 
	// the graphics pipeline to prepare them for drawing.
	m_Model->Render(
		m_pD3D->GetDeviceContext());

	// Render the model using the color shader.
	result = m_TextureShader->Render(
		m_pD3D->GetDeviceContext(), 
		m_Model->GetIndexCount(), 
		worldMatrix, 
		viewMatrix, 
		projectionMatrix,
		m_Model->GetTexture());

	if (!result)
	{
		return false;
	}

	m_pD3D->EndScene();

	return true;
}