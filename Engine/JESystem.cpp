#include "JESystem.h"

//==============================================
//			CONSTRUCTORS & DESTRUCTOR
//==============================================

//==============================================
JESystem::JESystem()
{
	m_pInput = 0;
	m_pGraphics = 0;
}


//==============================================
JESystem::JESystem(
	const JESystem & other
)
{

}


//==============================================
JESystem::~JESystem()
{

}


//==============================================
//				   METHODS
//==============================================

//==============================================
bool JESystem::Initialize()
{
	int screenWidth = 0;
	int screenHeight = 0;
	bool result;

	//==============================================
	// Inicjalizacja okna aplikacji
	InitializeWindows(
		screenWidth,
		screenHeight
	);
	//==============================================

	//==============================================
	// Utworzenie obiektu input. Ten obiekt bêdzie 
	// odpowiedzialny za obs³ugê klawiatury
	m_pInput = new JEInput;

	if (!m_pInput)
	{
		return false;
	}

	m_pInput->Initialize();

	//==============================================

	//==============================================
	// Utworzenie obiektu graphics. Ten obiekt bêdzie
	// odpowiedzialny za grafikê
	m_pGraphics = new JEGraphics;

	if (!m_pGraphics)
	{
		return false;
	}

	result = m_pGraphics->Initialize(
		screenWidth,
		screenHeight,
		m_hwnd
	);

	return result;
	//==============================================
}


//==============================================
void JESystem::Shutdown()
{
	//==============================================
	// Zwolnienie obiektu graphics
	if (m_pGraphics)
	{
		m_pGraphics->Shutdown();
		delete m_pGraphics;
		m_pGraphics = 0;
	}
	//==============================================

	//==============================================
	// Zwolnienie obiektu input
	if (m_pInput)
	{
		delete m_pInput;
		m_pInput = 0;
	}
	//==============================================

	ShutdownWindows();
}


//==============================================
void JESystem::Run()
{
	MSG msg;
	bool done, result;

	//==============================================
	// Inicjalizacja struktury message.
	ZeroMemory(&msg, sizeof(MSG));
	//==============================================

	//==============================================
	// G³ówna pêtla aplikacji
	done = false;

	while (!done)
	{
		//==============================================
		// Uchwyt okna wiadomoœci.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//==============================================

		//==============================================
		// Je¿eli otrzymamy sygna³ wyjœcia, wtedy
		// pêtla siê zakoñczy w przeciwnym wypadku
		// wykonuj obliczenia klatek.
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			result = Frame();

			if (!result)
			{
				done = true;
			}
		}
		//==============================================
	}
	//==============================================
}

//==============================================
LRESULT CALLBACK JESystem::MessageHandler(
	HWND hwnd, 
	UINT umsg, 
	WPARAM wparam, 
	LPARAM lparam
)
{
	switch (umsg)
	{
		// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input 
			// object so it can record that state.
			m_pInput->KeyDown((unsigned int)wparam);
			return 0;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input 
			// object so it can unset the state for that key.
			m_pInput->KeyUp((unsigned int)wparam);
			return 0;
		}

		// Any other messages send to the default message 
		// handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}


//==============================================
bool JESystem::Frame()
{
	bool result;

	if (m_pInput->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	result = m_pGraphics->Frame();

	return result;
}


//==============================================
void JESystem::InitializeWindows(
	int & screenWidth,
	int & screenHeight
)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	// WskaŸnik na aktualny obiekt
	pApplicationHandle = this;

	// Instancja aplikacji
	m_hInstance = GetModuleHandle(NULL);

	// Nazwa aplikacji
	m_applicationName = L"Engine";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth = 800;
		screenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and 
	// get the handle to it.
	m_hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		m_applicationName,
		m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY,
		screenWidth, screenHeight,
		NULL, NULL,
		m_hInstance, NULL);

	// Bring the window up on the screen and 
	// set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Ukrycie kursora
	ShowCursor(false);
}


//==============================================
void JESystem::ShutdownWindows()
{
	// Poka¿ kursor
	ShowCursor(true);

	//==============================================
	// Fix the display settings if leaving full 
	// screen mode.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}
	//==============================================

	//==============================================
	// Usuniêcie okna.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;
	//==============================================

	//==============================================
	// Usuniêcie instancji.
	UnregisterClass(
		m_applicationName, 
		m_hInstance);

	m_hInstance = NULL;
	//==============================================

	// Release the pointer to this class.
	pApplicationHandle = NULL;
}


//==============================================
LRESULT CALLBACK WndProc(
	HWND hwnd, 
	UINT umessage, 
	WPARAM wparam, 
	LPARAM lparam
)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}

		// All other messages pass to the message 
		// handler in the system class.
		default:
		{
			return pApplicationHandle->MessageHandler(
				hwnd, 
				umessage, 
				wparam, 
				lparam);
		}
	}
}