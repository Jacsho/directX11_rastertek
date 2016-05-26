#ifndef _JED3D_H_
#define _JED3D_H_

//==============================================
// LINKING
//==============================================
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

//==============================================
// INCLUDES
//==============================================
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <D3DX10math.h>

//==============================================
// Class name: JED3D
//==============================================
class JED3D
{
	//==============================================
	//				ATTRIBUTES
	//==============================================
	private:
		bool m_vsync_enabled;

		int m_videoCardMemory;

		char m_videoCardDescription[128];

		IDXGISwapChain * m_swapChain;

		ID3D11Device * m_device;

		ID3D11DeviceContext * m_deviceContext;

		ID3D11RenderTargetView * m_renderTargetView;

		ID3D11Texture2D * m_depthStencilBuffer;

		ID3D11DepthStencilState * m_depthStencilState;

		ID3D11DepthStencilView * m_depthStencilView;

		ID3D11RasterizerState * m_rasterState;

		D3DXMATRIX m_projectionMatrix;

		D3DXMATRIX m_worldMatrix;

		D3DXMATRIX m_orthoMatrix;


	//==============================================
	//			CONSTRUCTORS & DESTRUCTOR
	//==============================================
	public:
		JED3D();

		JED3D(
			const JED3D &
		);

		~JED3D();
	//==============================================
	//				   METHODS
	//==============================================
	public:
		bool Initialize(
			int screenWidth,
			int screenHeight,
			bool vsync,
			HWND hwnd,
			bool fullscreen,
			float screenDepth,
			float screenNear
		);

		void Shutdown();

		void BeginScene(
			float red,
			float green,
			float blue,
			float alpha
		);

		void EndScene();

	//==============================================
	//				   GETTERS
	//==============================================
	public:
		ID3D11Device * GetDevice();

		ID3D11DeviceContext * GetDeviceContext();

		void GetProjectionMatrix(
			D3DXMATRIX &
		);

		void GetWorldMatrix(
			D3DXMATRIX &
		);

		void GetOrthoMatrix(
			D3DXMATRIX &
		);

		void GetVideoCardInfo(
			char *, 
			int &
		);
};

#endif
