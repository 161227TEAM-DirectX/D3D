#include "stdafx.h"
#include "sceneManager.h"
#include "iGameNode.h"

HRESULT sceneManager::init(void)
{
	return S_OK;
}

void sceneManager::release(void)
{
	//정석적인 방법
	miSceneList iter = _mSceneList.begin();
	for (; iter != _mSceneList.end();)
	{
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mSceneList.clear();

	//for each(auto p in _mSceneList)
	//{
	//	p.second->release();
	//	SAFE_DELETE(p.second);
	//}
}

void sceneManager::update(void)
{
	//현재씬이 존재하면 해당하는 현재씬을 업데이트
	if (_currentScene)
	{
		_currentScene->update();
	}
}

void sceneManager::render(void)
{
	//현재씬이 존재하면 해당하는 현재씬을 업데이트
	if (_currentScene)
	{
		_currentScene->render();
	}
}

void sceneManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (_currentScene)
	{
		_currentScene->WndProc(hWnd, message, wParam, lParam);
	}
}


iGameNode * sceneManager::addScene(string sceneName, iGameNode * scene, bool isSceneChange)
{
	//씬이 없으니 널값 리턴
	if (!scene) return NULL;

	//씬이 있으니 맵에 담자
	_mSceneList.insert(make_pair(sceneName, scene));

	if (isSceneChange)
		changeScene(sceneName);
	else
		return scene;
}

HRESULT sceneManager::changeScene(string sceneName, bool isFirst)
{
	miSceneList find = _mSceneList.find(sceneName);

	//못찾았다면
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸려는 씬과 현재씬이 같냐?
	if (find->second == _currentScene) return E_FAIL;

	if (isFirst == false)
	{
		//_currentScene->release();
	}

	//여기까지 왔으면 문제 없으니 씬 초기화 하고 변경해준다
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}


//#include "gameNode.h"
//HRESULT sceneManager::init(void)
//{
//	return S_OK;
//}
//
//void sceneManager::release(void)
//{
//	//정석적인 방법
//	miSceneList iter = _mSceneList.begin();
//	for (; iter != _mSceneList.end();)
//	{
//		if (iter->second != NULL)
//		{
//			if (iter->second == _currentScene) iter->second->releaseGameNode();
//			SAFE_DELETE(iter->second);
//			iter = _mSceneList.erase(iter);
//		}
//		else
//		{
//			++iter;
//		}
//	}
//	_mSceneList.clear();
//
//	//for each(auto p in _mSceneList)
//	//{
//	//	p.second->release();
//	//	SAFE_DELETE(p.second);
//	//}
//}
//
//void sceneManager::update(void)
//{
//	//현재씬이 존재하면 해당하는 현재씬을 업데이트
//	if (_currentScene)
//	{
//		_currentScene->updateGameNode();
//	}
//}
//
//void sceneManager::render(void)
//{
//	//현재씬이 존재하면 해당하는 현재씬을 업데이트
//	if (_currentScene)
//	{
//		_currentScene->renderGameNode();
//	}
//}
//
//gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
//{
//	//씬이 없으니 널값 리턴
//	if (!scene) return NULL;
//
//	//씬이 있으니 맵에 담자
//	_mSceneList.insert(make_pair(sceneName, scene));
//
//	//씬매니져 종류 변경
//	g_eSceneManager = eSceneManager::E_GAMENODE;
//
//	return scene;
//}
//
//HRESULT sceneManager::changeScene(string sceneName)
//{
//	miSceneList find = _mSceneList.find(sceneName);
//
//	//못찾았다면
//	if (find == _mSceneList.end()) return E_FAIL;
//
//	//바꾸려는 씬과 현재씬이 같냐?
//	if (find->second == _currentScene) return E_FAIL;
//
//	//여기까지 왔으면 문제 없으니 씬 초기화 하고 변경해준다
//	if (SUCCEEDED(find->second->initGameNode()))
//	{
//		_currentScene = find->second;
//
//		return S_OK;
//	}
//
//	return E_FAIL;
//}