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
	m_LightShader = 0;
	m_Light = 0;
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
		-8.0f);

	// Create the model object.
	m_Model = new JEModel;

	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(
		m_pD3D->GetDevice(),
		"../Engine/data/cube.txt",
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

	// Create the light shader object.
	m_LightShader = new JELightShader;

	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_LightShader->Initialize(
		m_pD3D->GetDevice(), 
		hwnd);
	
	if (!result)
	{
		MessageBox(
			hwnd, 
			L"Could not initialize the light shader object.",
			L"Error", 
			MB_OK);

		return false;
	}

	// Create the light object.
	m_Light = new JELight;

	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetDiffuseColor(
		1.0f, 
		1.0f, 
		1.0f, 
		1.0f);

	m_Light->SetDirection(
		0.0f, 
		0.0f, 
		1.0f);

	return true;
}


//==============================================
void JEGraphics::Shutdown()
{
	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the color shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
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
	static float rotationY = 0.0f;
	static float rotationZ = 0.0f;

	// Update the rotation variable each frame.
	rotationY += (float)D3DX_PI * 0.005f;

	if (rotationY > 360.0f)
	{
		rotationY -= 360.0f;
	}

	rotationZ += (float)D3DX_PI * 0.001f;

	if (rotationZ > 360.0f)
	{
		rotationZ -= 360.0f;
	}

	result = Render(rotationY, rotationZ);

	return result;
}


//==============================================
bool JEGraphics::Render(
	float rotationY,
	float rotationZ
)
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

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	D3DXMATRIX matRotationY, matRotationZ;
	D3DXMatrixRotationY(&matRotationY, rotationY);
	D3DXMatrixRotationX(&matRotationZ, rotationZ);

	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &matRotationY);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &matRotationZ);

	// Put the model vertex and index buffers on 
	// the graphics pipeline to prepare them for drawing.
	m_Model->Render(
		m_pD3D->GetDeviceContext());

	// Render the model using the color shader.
	result = m_LightShader->Render(
		m_pD3D->GetDeviceContext(), 
		m_Model->GetIndexCount(), 
		worldMatrix, 
		viewMatrix, 
		projectionMatrix,
		m_Model->GetTexture(),
		m_Light->GetDirection(),
		m_Light->GetDiffuseColor());

	if (!result)
	{
		return false;
	}

	m_pD3D->EndScene();

	return true;
}