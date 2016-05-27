#include "JETexture.h"

//==============================================
//			CONSTRUCTORS & DESTRUCTOR
//==============================================

//==============================================
JETexture::JETexture()
{
	m_texture = 0;
}


//==============================================
JETexture::JETexture(
	const JETexture & other
)
{

}


//==============================================
JETexture::~JETexture()
{
	Shutdown();
}


//==============================================
//				   METHODS
//==============================================

//==============================================
bool JETexture::Initialize(
	ID3D11Device * device,
	WCHAR * fileName
)
{
	HRESULT result;

	// Load the texture in.
	result = D3DX11CreateShaderResourceViewFromFile(
		device, 
		fileName, 
		NULL, 
		NULL, 
		&m_texture, 
		NULL);

	if (FAILED(result))
	{
		return false;
	}

	return true;
}


//==============================================
void JETexture::Shutdown()
{
	// Release the texture resource.
	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}
}


//==============================================
//				   GETTERS
//==============================================

//==============================================
ID3D11ShaderResourceView * JETexture::GetTexture()
{
	return m_texture;
}