#pragma once

#define FILEPATH_MANAGER cFilepathManager::GetInstance()

class cFilepathManager
{
	SINGLETONE(cFilepathManager);

private:
	map<string, string> m_mapFilepath;

public:
	bool AddFilepath(string szKey, string szFilepath);
	string GetFilepath(string szKey);
};

