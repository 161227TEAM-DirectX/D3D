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
	
	//assert(szKey != "Å¸ÀÏ¸Ê_1" && "Å¸ÀÏ¸Ê µé¾î¿È");
	if (m_mapFilepath.find(szKey) != m_mapFilepath.end())
		return false;
	m_mapFilepath[szKey] = szFilepath;
	return true;
}

string cFilepathManager::GetFilepath(string szKey)
{
	string key = szKey;
	if (m_mapFilepath.find(szKey) == m_mapFilepath.end())
		return NULL;
	return m_mapFilepath[szKey];
}
