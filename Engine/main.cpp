#include "JESystem.h"


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR pScmdline,
	int iCmdshow)
{
	JESystem * System;
	bool result;

	//===================================================
	// Tworzymy obiekt System
	System = new JESystem;

	if (!System)
	{
		return 1;
	}
	//===================================================

	//===================================================
	// Inicjalizacja i uruchomienie obiektu system
	result = System->Initialize();

	if (result)
	{
		System->Run();
	}
	//===================================================

	//===================================================
	// Zamkniêcie i zwolnienie obiektu system
	System->Shutdown();
	delete System;
	System = 0;
	//===================================================

	return 0;

}