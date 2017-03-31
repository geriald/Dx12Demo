#pragma once

#include "stdafx.h"
#include "DxUtil.h"

class DxBase
{
public:
	DxBase(UINT width, UINT height, std::wstring name);
	virtual ~DxBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;

	UINT GetWidth() const { return m_width; }
	UINT GetHeight() const { return m_height; }
	const WCHAR* GetTitle() const { return m_title.c_str(); }

protected:
	void GetHardwareAdapter(IDXGIFactory2* pFactory, IDXGIAdapter1** ppAdapter);	//��ȡӲ��������
	void SetCustomWindowText(LPCWSTR text);

	UINT m_width;
	UINT m_height;
	float m_aspectRatio;	//��߱�

	bool m_isUseWarpDevice;	//�Ƿ�ʹ��warp device

private:
	std::wstring m_title;
};
