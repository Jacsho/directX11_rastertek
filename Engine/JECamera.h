#ifndef _JECAMERA_H_
#define _JECAMERA_H_


//==============================================
// INCLUDES 
//==============================================
#include <d3dx10math.h>


//==============================================
// Class name: JECamera
//==============================================
class JECamera
{
	//==============================================
	//				ATTRIBUTES
	//==============================================
	private:
		float m_positionX;

		float m_positionY;

		float m_positionZ;

		float m_rotationX;

		float m_rotationY;

		float m_rotationZ;

		D3DXMATRIX m_viewMatrix;
	//==============================================
	//			CONSTRUCTORS & DESTRUCTOR
	//==============================================
	public:
		JECamera();

		JECamera(
			const JECamera & other
		);

		~JECamera();
	//==============================================
	//				   METHODS
	//==============================================
	public:
		void Render();
	//==============================================
	//				   GETTERS
	//==============================================
	public:
		D3DXVECTOR3 GetPosition();

		D3DXVECTOR3 GetRotation();

		void GetViewMatrix(
			D3DXMATRIX & viewMatrix
		);
	//==============================================
	//				   SETTERS
	//==============================================
	public:
		void SetPosition(
			float x, 
			float y, 
			float z
		);

		void SetRotation(
			float x, 
			float y, 
			float z
		);
};

#endif
