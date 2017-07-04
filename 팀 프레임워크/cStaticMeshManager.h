#pragma once

#define MESHSTATIC_MANAGER cStaticMeshManager::GetInstance()

class cStaticMeshManager
{
private:
	SINGLETONE(cStaticMeshManager);

private:
	map<string, xMeshStatic*>	m_mapMeshStatic;

public:
	bool AddMeshStatic(string sKey, xMeshStatic* csMesh);
	xMeshStatic* GetMeshStatic(string sKey);
};

