#include "stdafx.h"
#include "cFilepathManager.h"


cFilepathManager::cFilepathManager()
{
}


cFilepathManager::~cFilepathManager()
{
	m_mapFilepath.clear();
}

bool cFilepathManager::AddFilepath(string szKey, string szFilepath)
{
	if (m_mapFilepath.find(szKey) != m_mapFilepath.end())
		return false;
	m_mapFilepath[szKey] = szFilepath;
	return true;
}

string cFilepathManager::GetFilepath(string szKey)
{
	if (m_mapFilepath.find(szKey) == m_mapFilepath.end())
		return NULL;
	return m_mapFilepath[szKey];
}
