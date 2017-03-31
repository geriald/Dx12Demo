#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "Common\d3dUtil.h"
#include "Common\GameTimer.h"
#include "Common\Input.h"

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

class D3d12Base
{
public:
	D3d12Base(HINSTANCE hInstance);
	D3d12Base(const D3d12Base& rhs) = delete;//��ֹ����
	D3d12Base& operator=(const D3d12Base& rhs) = delete;
	virtual ~D3d12Base();

public:
	static D3d12Base* GetApp();

	HINSTANCE AppInst()const;
	HWND      MainWnd()const;
	float     AspectRatio()const;

	bool Get4xMsaaState()const;
	void Set4xMsaaState(bool value);

	int Run();

	virtual bool Initialize();
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	virtual void CreateRtvAndDsvDescriptorHeaps();
	//�ı��С
	virtual void OnResize();						
	virtual void Update(const GameTimer& gt) = 0;
	virtual void Draw(const GameTimer& gt) = 0;

	//������Ӧ  �����װ��Input�࣬����ʹ��
	virtual void OnMouseDown(WPARAM btnState, int x, int y) { }
	virtual void OnMouseUp(WPARAM btnState, int x, int y) { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y) { }

protected:
	//��ʼ��
	bool InitMainWindow();
	bool InitDirect3D();
	void CreateCommandObjects();
	void CreateSwapChain();

	void FlushCommandQueue();

	ID3D12Resource* CurrentBackBuffer()const;
	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView()const;
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView()const;

	void CalculateFrameStats();

	void LogAdapters();
	void LogAdapterOutputs(IDXGIAdapter* adapter);
	void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

protected:

	static D3d12Base* m_app;

	HINSTANCE m_hInstance = nullptr; 
	HWND      m_hwnd = nullptr; 
	bool      m_isAppPaused = false;		// �Ƿ���ͣ
	bool      m_isMinimized = false;		// �Ƿ���С��
	bool      m_isMaximized = false;		// �Ƿ����
	bool      m_isResizing = false;			//�Ƿ����ڱ���ק
	bool      m_isFullscreenState = false;	// ȫ����

									   // �Ƿ���ö��ز���
	bool      m_4xMsaaState = false;    
	UINT      m_4xMsaaQuality = 0;      // quality level of 4X MSAA

									 
	GameTimer m_timer;

	//dxgi����
	Microsoft::WRL::ComPtr<IDXGIFactory4> m_pDxgiFactory;
	//������
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain;
	//�豸
	Microsoft::WRL::ComPtr<ID3D12Device> m_pD3dDevice;

	//�ϰ�����֤��һ֡��Ⱦ���
	Microsoft::WRL::ComPtr<ID3D12Fence> m_pFence;
	UINT64 m_currentFence = 0;

	//�������
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_pCommandQueue;
	//���������
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_pCommandAllocator;
	//ͼ�������б�
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_pCommandList;

	static const int ms_swapChainBufferCount = 2;
	int m_currBackBuffer = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> m_pSwapChainBuffer[ms_swapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> m_pDepthStencilBuffer;

	//��Ⱦ����Ŀ��������
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_pRtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_pDsvHeap;

	//�ӿ�
	D3D12_VIEWPORT m_screenViewport;									
	D3D12_RECT m_scissorRect;

	UINT m_rtvDescriptorSize = 0;
	UINT m_dsvDescriptorSize = 0;
	UINT m_cbvSrvUavDescriptorSize = 0;

	//�������͡�format����ʾ����ȵ�
	std::wstring m_mainWndCaption = L"d3d12Base";
	D3D_DRIVER_TYPE m_d3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
	DXGI_FORMAT m_backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT m_depthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	int m_clientWidth = 800;
	int m_clientHeight = 600;

};

