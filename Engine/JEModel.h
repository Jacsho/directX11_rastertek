#ifndef _JEMODEL_H_
#define _JEMODEL_H_

//==============================================
// INCLUDES
//==============================================
#include <d3d11.h>
#include <d3dx10math.h>

//==============================================
// MY INCLUDES
//==============================================
#include "JETexture.h"

//==============================================
// Class name: JEModel
//==============================================
class JEModel
{
	//==============================================
	//				STRUCTURES
	//==============================================
	private:
		struct VertexType
		{
			D3DXVECTOR3 position;
			D3DXVECTOR2 texture;
			D3DXVECTOR3 normal;
		};

	//==============================================
	//				ATTRIBUTES
	//==============================================
	private:
		ID3D11Buffer * m_vertexBuffer;

		int m_vertexCount;

		ID3D11Buffer * m_indexBuffer;

		int m_indexCount;

		JETexture * m_Texture;
	//==============================================
	//			CONSTRUCTORS & DESTRUCTOR
	//==============================================
	public:
		JEModel();

		JEModel(
			const JEModel &
		);

		~JEModel();
	//==============================================
	//				   METHODS
	//==============================================
	public:
		bool Initialize(
			ID3D11Device * device,
			WCHAR * textureFileName
		);

		void Shutdown();

		void Render(
			ID3D11DeviceContext * deviceContext
		);

	private:
		bool InitializeBuffers(
			ID3D11Device * device
		);

		void ShutdownBuffers();

		void RenderBuffers(
			ID3D11DeviceContext * deviceContext
		);

		bool LoadTexture(
			ID3D11Device * device,
			WCHAR * fileName
		);

		void ReleaseTexture();
	//==============================================
	//				   GETTERS
	//==============================================
	public:
		int GetIndexCount();

		ID3D11ShaderResourceView * GetTexture();
};

#endif
