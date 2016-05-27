#ifndef _JEGRAPHICS_H_
#define _JEGRAPHICS_H_


//==============================================
// INCLUDES
//==============================================
//#include <Windows.h>

//==============================================
// MY INCLUDES
//==============================================
#include "JED3D.h"
#include "JECamera.h"
#include "JEModel.h"
#include "JEColorShader.h"

//==============================================
// GLOBALS
//==============================================
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

//==============================================
// Class name: JEGraphics
//==============================================
class JEGraphics
{
	//==============================================
	//				ATTRIBUTES
	//==============================================
	private:
		JED3D * m_pD3D;

		JECamera * m_Camera;

		JEModel * m_Model;

		JEColorShader * m_ColorShader;

	//==============================================
	//			CONSTRUCTORS & DESTRUCTOR
	//==============================================
	public:
		JEGraphics();

		JEGraphics(
			const JEGraphics &
		);

		~JEGraphics();
		
	//==============================================
	//				   METHODS
	//==============================================
	public:
		bool Initialize(
			int screenWidth,
			int screenHeight,
			HWND hwnd
		);

		void Shutdown();

		bool Frame();

private:

	bool Render();
};

#endif
