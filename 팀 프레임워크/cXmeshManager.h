#pragma once

#define XMESH_MANAGER cXmeshManager::GetInstance()

class cXmeshManager
{
	SINGLETONE(cXmeshManager);

private:
	map<string, xMesh*>	m_mapXstatic;		//스태틱 메쉬
	map<string, xMesh*>	m_mapXskinned;		//스킨드 메쉬

public:
	bool AddXmeshStatic(string sKey, xMesh* pxMeshStatic);
	xMesh* GetXmeshStatic(string sKey);

	bool AddXmeshSkinned(string sKey, xMesh* pxMeshSkinned);
	xMesh* GetXmeshSkinned(string sKey);
};

