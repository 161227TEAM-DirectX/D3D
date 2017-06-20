#pragma once

#define XMESH_MANAGER cXmeshManager::GetInstance()

class cXmeshManager
{
	SINGLETONE(cXmeshManager);

private:
	map<string, xMesh*>	m_mapXstatic;		//����ƽ �޽�
	map<string, xMesh*>	m_mapXskinned;		//��Ų�� �޽�

public:
	bool AddXmeshStatic(string sKey, xMesh* pxMeshStatic);
	xMesh* GetXmeshStatic(string sKey);

	bool AddXmeshSkinned(string sKey, xMesh* pxMeshSkinned);
	xMesh* GetXmeshSkinned(string sKey);
};

