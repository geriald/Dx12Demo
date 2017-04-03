#include "ModelImporter.h"

using namespace std;
using namespace DirectX;

ModelImporter::ModelImporter()
{

}

ModelImporter::~ModelImporter()
{

}

bool ModelImporter::LoadModel(const std::string filepath)
{
	Assimp::Importer importer;
	const aiScene* pScene = importer.ReadFile(filepath, 
		aiProcess_Triangulate | //���ǻ�
		aiProcess_FlipUVs | //��ת
		aiProcess_CalcTangentSpace | //�������߿ռ�
		aiProcess_FixInfacingNormals | //����������
		aiProcess_ConvertToLeftHanded //��Ϊ����ϵ
	);

	if (!pScene)
	{
		MessageBoxA(NULL, importer.GetErrorString(), "Error", MB_OK);
		return false;
	}

	this->ProcessNode(pScene->mRootNode, pScene);
}

void ModelImporter::ProcessNode(aiNode* node, const aiScene* scene)
{
	// ��ӵ�ǰ�ڵ��е�����Mesh
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(this->ProcessMesh(mesh, scene));
	}
	// �ݹ鴦��ýڵ������ڵ�
	for (int i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], scene);
	}
}

ModelImporter::ModelMesh ModelImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<ModelVertex> vertices(0);
	vector<UINT> indices(0);
	ModelMaterial material;

	//��������
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		ModelVertex vertex;

		vertex.Pos = XMFLOAT3
		{
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		};

		
		vertex.Normal = XMFLOAT3
		{
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			 mesh->mNormals[i].z
		};
		
		if (mesh->mTextureCoords[0]) // �Ƿ����uv
		{
			vertex.TexC = XMFLOAT2
			{
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			};
		}
		else
			vertex.TexC = XMFLOAT2{ 0.0f, 0.0f };

		
		vertex.TangentU = XMFLOAT3
		{
			mesh->mTangents[i].x,
			mesh->mTangents[i].y,
			mesh->mTangents[i].z
		};

		vertices.push_back(vertex);
	}
	
	//��������
	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	//��������
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

		//��������������,ֻ����һ��
		for (int i = 0; i < mat->GetTextureCount(aiTextureType_DIFFUSE); ++i)
		{
			aiString str;
			mat->GetTexture(aiTextureType_DIFFUSE, i, &str);

			char path[100];
			material.Name = "diffuse" + to_string(m_meshes.size());
			memcpy(path, str.data, str.length + 1);
			material.DiffuseMapName = path;
		}

		for (int i = 0; i < mat->GetTextureCount(aiTextureType_NORMALS); ++i)
		{
			aiString str;
			mat->GetTexture(aiTextureType_NORMALS, i, &str);

			char path[100];
			material.Name = "normal" + to_string(m_meshes.size());
			memcpy(path, str.data, str.length + 1);
			material.NormalMapName = path;
		}

	}

	return ModelMesh(vertices, indices, material);
}