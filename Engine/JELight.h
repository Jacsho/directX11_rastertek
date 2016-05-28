#ifndef _JELIGHT_H_
#define _JELIGHT_H_

//==============================================
// INCLUDES
//==============================================
#include <d3dx10math.h>

//==============================================
// Class name: JELight
//==============================================
class JELight
{
	//==============================================
	//				ATTRIBUTES
	//==============================================
	private:
		D3DXVECTOR4 m_diffuseColor;

		D3DXVECTOR3 m_direction;
	//==============================================
	//			CONSTRUCTORS & DESTRUCTOR
	//==============================================
	public:
		JELight();

		JELight(
			const JELight & other
		);

		~JELight();
	//==============================================
	//				   METHODS
	//==============================================

	//==============================================
	//				   GETTERS
	//==============================================
	public:
		D3DXVECTOR4 GetDiffuseColor();

		D3DXVECTOR3 GetDirection();
	//==============================================
	//				   SETTERS
	//==============================================
	public:
		void SetDiffuseColor(
			float red,
			float green,
			float blue,
			float alpha
		);

		void SetDirection(
			float x, 
			float y, 
			float z
		);
};

#endif
