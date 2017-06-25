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

	void render(string sKey);
	void render(string sKey, float srcX, float srcY, float srcWidth, float srcHeight, float moveX = 0.0f, float moveY = 0.0f);
	void render();
};

