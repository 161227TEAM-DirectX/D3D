#include "stdafx.h"
#include "cSceneManager.h"
#include "iScene.h"

cSceneManager::cSceneManager()
	: m_pCurrentScene(NULL)
{
}


cSceneManager::~cSceneManager()
{
}

bool cSceneManager::AddScene(string sKey, iScene * pScene)
{
	if(m_mapScene.find(sKey) != m_mapScene.end())
		return false;
	m_mapScene[sKey] = pScene;

	//씬매니져 종류 변경
	g_eSceneManager = eSceneManager::E_ISCENE;
}

bool cSceneManager::ChangeScene(string sKey)
{
	//씬을 못찾았으면 펄스를 반환
	if(m_mapScene.find(sKey) == m_mapScene.end())
		return false;

	//씬을 찾았으면 현재씬을 릴리즈시키고 erase시킨다.
	iScene* scene = m_pCurrentScene;
	m_pCurrentScene = m_mapScene[sKey];

	//증가된 RefCOunt 내려줌
	SAFE_RELEASE(scene);
	m_mapScene.erase(sKey);

	m_pCurrentScene->Setup();

	return true;
}

iScene * cSceneManager::GetScene(string sKey)
{
	if(m_mapScene.find(sKey) == m_mapScene.end())
		return NULL;
	return m_mapScene[sKey];
}

iScene * cSceneManager::GetCurrentScene()
{
	return m_pCurrentScene;
}

void cSceneManager::Destroy()
{
	SAFE_RELEASE(m_pCurrentScene);
	for each(auto p in m_mapScene)
	{
		SAFE_RELEASE(p.second);
	}

	m_mapScene.clear();
}

void cSceneManager::Setup()
{
	if(m_pCurrentScene)
	{
		m_pCurrentScene->Setup();
	}
}

void cSceneManager::Update()
{
	if(m_pCurrentScene)
	{
		m_pCurrentScene->Update();
	}
}

void cSceneManager::Render()
{
	if(m_pCurrentScene)
	{
		m_pCurrentScene->Render();
	}
}

void cSceneManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(m_pCurrentScene)
	{
		m_pCurrentScene->WndProc(hWnd, message, wParam, lParam);
	}
}
