#pragma once

#define DXIMG_MANAGER cDxImgManager::GetInstance()

class cDxImg;

class cDxImgManager
{
	SINGLETONE(cDxImgManager);

private:
	map<string, cDxImg*> m_mapDxImg;
	vector<cDxImg*>     m_vecDxImg;
	
public:
	bool AddDxImg(string sKey, cDxImg* dxImg);
	cDxImg* GetDxImg(string sKey);

	void render();
};

