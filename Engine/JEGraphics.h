#ifndef _JEGRAPHICS_H_
#define _JEGRAPHICS_H_


//==============================================
// INCLUDES
//==============================================
#include <Windows.h>


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
