#include "stdafx.h"
#include "cStaticMeshManager.h"


cStaticMeshManager::cStaticMeshManager()
{
}


cStaticMeshManager::~cStaticMeshManager()
{
}

bool cStaticMeshManager::AddMeshStatic(string sKey, xMeshStatic * csMesh)
{
	if (m_mapMeshStatic.find(sKey) != m_mapMeshStatic.end())
		return false;
	m_mapMeshStatic[sKey] = csMesh;
	return true;
}

xMeshStatic * cStaticMeshManager::GetMeshStatic(string sKey)
{
	if (m_mapMeshStatic.find(sKey) == m_mapMeshStatic.end())
		return NULL;
	return m_mapMeshStatic[sKey];
}
