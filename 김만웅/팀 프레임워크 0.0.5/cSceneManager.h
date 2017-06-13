#pragma once

class iScene;

#define SCENE_MANAGER cSceneManager::GetInstance()

class cSceneManager
{
private:
	map<string, iScene*> m_mapScene;
	iScene*	m_pCurrentScene;

public:
	SINGLETONE(cSceneManager);

	bool AddScene(string sKey, iScene* pScene);
	bool ChangeScene(string sKey);

	iScene* GetScene(string sKey);
	iScene* GetCurrentScene();

	void Destroy();

public:
	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

