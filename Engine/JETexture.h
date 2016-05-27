#ifndef _JETEXTURE_H_
#define _JETEXTURE_H_

//==============================================
// INCLUDES
//==============================================
#include <d3d11.h>
#include <d3dx11tex.h>

//==============================================
// Class name: JETexture
//==============================================
class JETexture
{
	//==============================================
	//				ATTRIBUTES
	//==============================================
	private:
		ID3D11ShaderResourceView * m_texture;
	//==============================================
	//			CONSTRUCTORS & DESTRUCTOR
	//==============================================
	public:
		JETexture();

		JETexture(
			const JETexture & other
		);

		~JETexture();
	//==============================================
	//				   METHODS
	//==============================================
	public:
		bool Initialize(
			ID3D11Device * device,
			WCHAR * fileName
		);

		void Shutdown();
	//==============================================
	//				   GETTERS
	//==============================================
	public:
		ID3D11ShaderResourceView * GetTexture();
};

#endif
