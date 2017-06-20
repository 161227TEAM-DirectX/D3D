#include "stdafx.h"
#include "cXmeshManager.h"


cXmeshManager::cXmeshManager()
{
}


cXmeshManager::~cXmeshManager()
{
	m_mapXstatic.clear();
	m_mapXskinned.clear();
}

bool cXmeshManager::AddXmeshStatic(string sKey, xMesh * pxMeshStatic)
{
	if (m_mapXstatic.find(sKey) != m_mapXstatic.end())
		return false;
	m_mapXstatic[sKey] = pxMeshStatic;
	return true;
}

xMesh * cXmeshManager::GetXmeshStatic(string sKey)
{
	if (m_mapXstatic.find(sKey) == m_mapXstatic.end())
		return NULL;
	return m_mapXstatic[sKey];
}

bool cXmeshManager::AddXmeshSkinned(string sKey, xMesh * pxMeshSkinned)
{
	if (m_mapXskinned.find(sKey) != m_mapXskinned.end())
		return false;
	m_mapXskinned[sKey] = pxMeshSkinned;
	return true;
}

xMesh * cXmeshManager::GetXmeshSkinned(string sKey)
{
	if (m_mapXskinned.find(sKey) == m_mapXskinned.end())
		return NULL;
	return m_mapXskinned[sKey];
}
