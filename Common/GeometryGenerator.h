#ifndef _GEOMETRY_GENERATOR_H
#define _GEOMETRY_GENERATOR_H

#include<vector>

class GeometryGenerator
{
private:
	GeometryGenerator() {}
public:
	//����ģʽ
	static GeometryGenerator* GetInstance()
	{
		static GeometryGenerator instance;
		return &instance;
	}

	//����һ��ͨ�õĶ���ṹ��λ�á����ߡ����ߡ���������
	struct Vertex
	{
		Vertex() {}
		Vertex(const XMFLOAT3 _pos, XMFLOAT3 _normal, XMFLOAT3 _tangent, XMFLOAT2 _tex) :
			pos(_pos), normal(_normal), tangent(_tangent), tex(_tex) {}

		XMFLOAT3	pos;
		XMFLOAT3	normal;
		XMFLOAT3	tangent;
		XMFLOAT2	tex;
	};

	//��������ṹ�����㼯��+��������
	struct MeshData
	{
		std::vector<Vertex>	vertices;
		std::vector<UINT>	indices;
	};

	//����һ�������壺ָ����(X����)����(Y����)����(Z����)
	void CreateBox(float width, float height, float depth, MeshData &mesh);

	//����һ��������ӣ�ָ���ܿ��(X����)���ܸ߶�(Z����); m��nΪ���߷����ϵĸ�������
	void CreateGrid(float width, float height, UINT m, UINT n, MeshData &mesh);

	//����һ��Բ��(�����ϡ���������)��ָ���϶˰뾶(topRadius)���¶˰뾶(bottomRadius)���߶�(height)��
	//sllice��stack
	void CreateCylinder(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData &mesh);
	
	//���ֳɵ�Բ������Ͽ�
	void AddCylinderTopCap(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData &mesh);
	
	//���ֳɵ�Բ������¿�
	void AddCylinderBottomCap(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData &mesh);
	
	//����һ�����壺ָ���뾶(radius)��slice��stack
	void CreateSphere(float radius, int slice, int stack, MeshData &mesh);
};

#endif//_GEOMETRY_GENERATOR_H
