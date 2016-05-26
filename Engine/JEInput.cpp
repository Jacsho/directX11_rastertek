#include "JEInput.h"


//==============================================
//			CONSTRUCTORS & DESTRUCTOR
//==============================================

//==============================================
JEInput::JEInput()
{
}


//==============================================
JEInput::JEInput(const JEInput& other)
{
}


//==============================================
JEInput::~JEInput()
{
}


//==============================================
//				   METHODS
//==============================================

//==============================================
void JEInput::Initialize()
{
	for (int i = 0; i<256; i++)
	{
		m_keys[i] = false;
	}
}


//==============================================
void JEInput::KeyDown(unsigned int input)
{
	m_keys[input] = true;
}


//==============================================
void JEInput::KeyUp(unsigned int input)
{
	m_keys[input] = false;
}


//==============================================
bool JEInput::IsKeyDown(unsigned int key)
{
	return m_keys[key];
}