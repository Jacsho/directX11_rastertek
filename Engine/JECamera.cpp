#include "JECamera.h"

//==============================================
//			CONSTRUCTORS & DESTRUCTOR
//==============================================

//==============================================
JECamera::JECamera()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}


//==============================================
JECamera::JECamera(
	const JECamera & other
)
{

}


//==============================================
JECamera::~JECamera()
{

}


//==============================================
//				   METHODS
//==============================================

//==============================================
void JECamera::Render()
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), 
	// and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, 
	// pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(
		&rotationMatrix, 
		yaw, 
		pitch, 
		roll);

	// Transform the lookAt and up vector by the 
	// rotation matrix so the view is correctly 
	// rotated at the origin.
	D3DXVec3TransformCoord(
		&lookAt, 
		&lookAt, 
		&rotationMatrix);

	D3DXVec3TransformCoord(
		&up, 
		&up, 
		&rotationMatrix);

	// Translate the rotated camera position to the 
	// location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(
		&m_viewMatrix, 
		&position, 
		&lookAt, 
		&up);
}


//==============================================
//				   GETTERS
//==============================================

//==============================================
D3DXVECTOR3 JECamera::GetPosition()
{
	return D3DXVECTOR3(
		m_positionX, 
		m_positionY, 
		m_positionZ);
}


//==============================================
D3DXVECTOR3 JECamera::GetRotation()
{
	return D3DXVECTOR3(
		m_rotationX, 
		m_rotationY, 
		m_rotationZ);
}


//==============================================
void JECamera::GetViewMatrix(
	D3DXMATRIX & viewMatrix
)
{
	viewMatrix = m_viewMatrix;
}


//==============================================
//				   SETTERS
//==============================================

//==============================================
void JECamera::SetPosition(
	float x,
	float y,
	float z
)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
}


//==============================================
void JECamera::SetRotation(
	float x,
	float y,
	float z
)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
}