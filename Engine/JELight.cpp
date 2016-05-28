#include "JELight.h"

//==============================================
//			CONSTRUCTORS & DESTRUCTOR
//==============================================

//==============================================
JELight::JELight()
{

}


//==============================================
JELight::JELight(
	const JELight & other
)
{

}


//==============================================
JELight::~JELight()
{

}


//==============================================
//				   METHODS
//==============================================

//==============================================
//				   GETTERS
//==============================================

//==============================================
D3DXVECTOR4 JELight::GetDiffuseColor()
{
	return m_diffuseColor;
}


//==============================================
D3DXVECTOR3 JELight::GetDirection()
{
	return m_direction;
}


//==============================================
//				   SETTERS
//==============================================

//==============================================
void JELight::SetDiffuseColor(
	float red, 
	float green, 
	float blue, 
	float alpha
)
{
	m_diffuseColor = D3DXVECTOR4(
		red, 
		green, 
		blue, 
		alpha);
}


//==============================================
void JELight::SetDirection(
	float x,
	float y,
	float z
)
{
	m_direction = D3DXVECTOR3(
		x, 
		y, 
		z);
}