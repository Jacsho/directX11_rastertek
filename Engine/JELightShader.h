#ifndef _JELIGHTESHADER_H_
#define _JELIGHTESHADER_H_


//==============================================
// INCLUDES 
//==============================================
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>
using namespace std;


//==============================================
// Class name: JELightShader
//==============================================
class JELightShader
{
	//==============================================
	//				STRUCTURES
	//==============================================
	private:
		struct MatrixBufferType
		{
			D3DXMATRIX world;
			D3DXMATRIX view;
			D3DXMATRIX projection;
		};

		struct LightBufferType
		{
			D3DXVECTOR4 diffuseColor;
			D3DXVECTOR3 lightDirection;
			float padding;  // Added extra padding so 
							// structure is a multiple 
							// of 16 for CreateBuffer 
							// function requirements.
		};
	//==============================================
	//				ATTRIBUTES
	//==============================================
	private:
		ID3D11VertexShader * m_vertexShader;

		ID3D11PixelShader * m_pixelShader;

		ID3D11InputLayout * m_layout;

		ID3D11Buffer * m_matrixBuffer;

		ID3D11SamplerState * m_sampleState;

		ID3D11Buffer * m_lightBuffer;
	//==============================================
	//			CONSTRUCTORS & DESTRUCTOR
	//==============================================
	public:
		JELightShader();

		JELightShader(
			const JELightShader & other
		);

		~JELightShader();
	//==============================================
	//				   METHODS
	//==============================================
	public:
		bool Initialize(
			ID3D11Device * device, 
			HWND hwnd
		);

		void Shutdown();

		bool Render(
			ID3D11DeviceContext * deviceContext,
			int indexCount,
			D3DXMATRIX worldMatrix,
			D3DXMATRIX viewMatrix,
			D3DXMATRIX projectionMatrix,
			ID3D11ShaderResourceView * texture,
			D3DXVECTOR3 lightDirection,
			D3DXVECTOR4 diffuseColor
		);

	private:
		bool InitializeShader(
			ID3D11Device * device,
			HWND hwnd,
			WCHAR * vsFilename,
			WCHAR * psFilename
		);

		void ShutdownShader();

		void OutputShaderErrorMessage(
			ID3D10Blob * errorMessage,
			HWND hwnd,
			WCHAR * shaderFilename
		);

		void RenderShader(
			ID3D11DeviceContext * deviceContext,
			int indexCount
		);

	//==============================================
	//				   SETTERS
	//==============================================
	private:
		bool SetShaderParameters(
			ID3D11DeviceContext * deviceContext,
			D3DXMATRIX worldMatrix,
			D3DXMATRIX viewMatrix,
			D3DXMATRIX projectionMatrix,
			ID3D11ShaderResourceView * texture,
			D3DXVECTOR3 lightDirection,
			D3DXVECTOR4 diffuseColor
		);
};

#endif