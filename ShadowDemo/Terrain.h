#pragma once
#include <vector>
#include <DirectXMath.h>
#include "Common\d3dUtil.h"
#include "Common\MathHelper.h"
#include "FrameResource.h"

class Terrain
{
public:
	Terrain(float width, float height, UINT m, UINT n, float scale);
	Terrain(const Terrain& rhs) = delete;
	Terrain& operator =(const Terrain& rhs) = delete;
	~Terrain();

private:
	bool InitTerrain(float width, float height, UINT m, UINT n, float scale);
	bool ReadRawFile(std::string filePath);										//�Ӹ߶�ͼ��ȡ�߶���Ϣ
	void ComputeNomal(Vertex& v1, Vertex& v2, Vertex& v3, DirectX::XMFLOAT3& normal);	//���㷨��
	void XMFloat3Add(DirectX::XMFLOAT3& dst, DirectX::XMFLOAT3& vec3);
	void XMFloat3Normalize(DirectX::XMFLOAT3& vec3);
	void CalcTangent(DirectX::XMFLOAT3& tangent, DirectX::XMFLOAT3& normal);


	std::vector<float>	m_heightInfos;		//�߶�ͼ�߶���Ϣ
	int		m_cellsPerRow;					//ÿ�е�Ԫ����
	int		m_cellsPerCol;					//ÿ�е�Ԫ����
	int		m_verticesPerRow;				//ÿ�ж�����
	int		m_verticesPerCol;				//ÿ�ж�����
	int		m_numsVertices;					//��������
	float	m_width;						//���ο��
	float	m_height;						//���θ߶�
	float	m_heightScale;					//�߶�����ϵ��

	//��ͬ���ζ�Ӧ�ĸ߶ȣ��Ա���費ͬ�Ĳ�����ͼshader�ȵ�
	float   m_waterHeight;
	float	m_groundHeight;
	float   m_roadHeight;
	float   m_grassHeight;

public:
	std::unordered_map<std::string, std::vector<Vertex>>  m_vertexItems;	//��ͬ���εĶ��㼯��
	std::unordered_map<std::string, std::vector<UINT>> m_indexItems;		//��ͬ���ε���������
};

