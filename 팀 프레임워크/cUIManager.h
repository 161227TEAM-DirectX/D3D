#pragma once

#define UI_MANAGER cUIManager::GetInstance()

class cDxImgUI;

class cUIManager
{
	SINGLETONE(cUIManager);

private:
	map<string, cDxImgUI*> m_mapUI;
	vector<cDxImgUI*>	   m_vecUI;

public:
	bool AddUI(string sKey, cDxImgUI* ui);
	cDxImgUI* GetUI(string sKey);

	void update();
	void render(string sKey);
	void render();
};

