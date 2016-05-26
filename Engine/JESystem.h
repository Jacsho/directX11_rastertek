#ifndef _JESYSTEM_H_
#define _JESYSTEM_H_

//==============================================
// PRE-PROCESSING DIRECTIVES
//==============================================
#define WIN32_LEAN_AND_MEAN

//==============================================
// INCLUDES
//==============================================
#include <Windows.h>

//==============================================
// MY CLASS INCLUDES
//==============================================
#include "JEInput.h"
#include "JEGraphics.h"

//==============================================
// Class name: JESystem
//==============================================
class JESystem
{
	//==============================================
	//				ATTRIBUTES
	//==============================================
	private:
		LPCWSTR m_applicationName;

		HINSTANCE m_hInstance;

		HWND m_hwnd;

		JEInput * m_pInput;

		JEGraphics * m_pGraphics;

	//==============================================
	//			CONSTRUCTORS & DESTRUCTOR
	//==============================================
	public:
		JESystem();

		JESystem(
			const JESystem &
		);

		~JESystem();

	//==============================================
	//				   METHODS
	//==============================================
	public:
		bool Initialize();

		void Shutdown();

		void Run();

		LRESULT CALLBACK MessageHandler(
			HWND hwnd,
			UINT umsg,
			WPARAM wparam,
			LPARAM lparam
		);

	private:
		bool Frame();

		void InitializeWindows(
			int &,
			int &
		);

		void ShutdownWindows();
};

//==============================================
// FUNCTION PROTOTYPES
//==============================================
static LRESULT CALLBACK WndProc(
	HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam
);

//==============================================
// GLOBALS
//==============================================
static JESystem * pApplicationHandle = 0;

#endif 
