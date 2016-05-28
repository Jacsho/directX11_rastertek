#ifndef _JEMODEL_H_
#define _JEMODEL_H_

//==============================================
// INCLUDES
//==============================================
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;

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

		struct ModelType
		{
			float x, y, z;
			float tu, tv;
			float nx, ny, nz;
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

		ModelType * m_model;
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
			char * modelFileName,
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

		bool LoadModel(
			char * fileName
		);

		void ReleaseModel();
	//==============================================
	//				   GETTERS
	//==============================================
	public:
		int GetIndexCount();

		ID3D11ShaderResourceView * GetTexture();
};

#endif
