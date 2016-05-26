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
	else
	{
		System->Shutdown();
		delete System;
		System = 0;
		return 2;
	}
	//===================================================

	//===================================================
	// Zamkni�cie i zwolnienie obiektu system
	System->Shutdown();
	delete System;
	System = 0;
	//===================================================

	return 0;

}