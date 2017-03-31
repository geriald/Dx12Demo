#pragma once

#include "DxBase.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

class HelloTriangle : public DxBase
{
public:
	HelloTriangle(UINT width, UINT height, std::wstring name);
	
	virtual void Init();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

private:
	static const UINT m_frameCount = 2;

	//����ṹ
	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

	D3D12_VIEWPORT m_viewPort;								//�ӿ�
	D3D12_RECT m_scissorRect;
	ComPtr<IDXGISwapChain3> m_pSwapChain;					//������
	ComPtr<ID3D12Device> m_pDevice;
	ComPtr<ID3D12Resource> m_pRenderTargets[m_frameCount];
	ComPtr<ID3D12CommandAllocator>	m_pCommandAllocator;	//���������
	ComPtr<ID3D12CommandQueue>	m_pCommandQueue;			//�������
	ComPtr<ID3D12RootSignature> m_pRootSignature;
	ComPtr<ID3D12DescriptorHeap> m_pRtvHeap;
	ComPtr<ID3D12PipelineState> m_pPipelineState;			//����״̬
	ComPtr<ID3D12GraphicsCommandList> m_pCommandList;		//ͼ�������б�
	UINT m_rtvDescriptorSize;

	ComPtr<ID3D12Resource> m_vertexBuffer;					//���㻺��
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

	UINT m_frameIndex;					//fence��֡Ϊ��λ�����Եȴ����������һ֡������.����ID3D12Fence::SetEventOnCompletion
										//��ID3D12CommandQueue::Signal�����źŲ���, ����֮��ȴ�����,
	HANDLE m_fenceEvent;
	ComPtr<ID3D12Fence> m_pFence;
	UINT64 m_fenceValue;

	void LoadPipeline();
	void LoadAssets();
	void PopulateCommandList();
	void WaitForPreviousFrame();
};

